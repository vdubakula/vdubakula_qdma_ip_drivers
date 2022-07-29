#!/bin/bash

#set -x
if [ $# -gt 1 ];then
	echo "Usage: ./parser <full path of directory>" 
	exit 1
fi
dir=$1

if [[ ! -d $dir ]];then
	echo "Directory does not exist"
	exit 1
fi

toKB()
{
local value=$1
local unit=$2
if [[ "$unit" == "KB/s" ]];then
	echo "$value"
elif [[ "$unit" == "MB/s" ]];then
	echo "$(echo "scale=4; $value*1000" | bc -l)"
elif [[ "$unit" == "GB/s" ]];then
	echo "$(echo "scale=4; $value*1000000" | bc -l)"
else
	echo "$(echo "scale=4; $value" | bc -l)"
fi
}

getusec()
{
local value=$1
local unit=$2
if [[ "$unit" == "sec" ]];then
	echo "$(echo "scale=6; $value*1000000" | bc -l)"
elif [[ "$unit" == "msec" ]];then
	echo "$(echo "scale=6; $value*1000" | bc -l)"
elif [[ "$unit" == "usec" ]];then
	echo "$value"
elif [[ "$unit" == "nsec" ]];then
	echo "$(echo "scale=4; $value/1000" | bc -l)"
fi

}

parse_dir()
{
	resdir=`basename $1`
	topdir=`dirname ${1}`
	direc=`basename ${topdir}`
	filename="${topdir}/perf_result_${direc}.csv"
	if [[ ! -f $filename ]];then
		touch ${filename}
	fi
	cd $1
	declare -a fiofils
	declare -a sarfils
	readarray fiofils < <(find . -type f -name "fio*" | sort -k 2 -t _ -g)
	readarray sarfils < <(find . -type f -name "sar*" | sort -k 2 -t _ -g)
	
	echo $resdir >> $filename
	echo "iosize(KiB)"," ","H2C"," "," ","C2H" >> $filename
	echo " ","throughput(KB/s)","latency(usec)","CPU%","throughput(KB/s)","latecny(usec)","CPU%">>$filename
	
	length=${#fiofils[@]}
	
	if [[ "$direc" == "unidir" ]];then
		for ((i=0; i<$length; i++))
		do
			size=$(echo "${fiofils[i]}" | awk -F'[_.]' '{print $3}')  #extract io size from file name
			#size=$(numfmt --to=iec-i --suffix=B --padding=7 $size)
			size=$(echo "scale=4; $size/1024" | bc -l) #convert io size to kB
			c2hth=$(awk '/bw=/{print $3}' ${fiofils[i]} | sed 's/(//g' | sed 's/),//g') # extract bw
			unit=$(echo $c2hth | awk -F '[0-9,.]*' '{print $2}') #extract bw unit
			value=$(echo $c2hth | sed 's/[^0-9,.]*//g') #extract bw value
			c2hth=$(toKB $value $unit) #calculate in kiB
			read units <<< $(awk -F " " '/clat/{print $2;exit;}' ${fiofils[i]} | awk -F "[(,)]" '{print $2}')
			c2hlat=$(awk -F "," '/clat/{print $3}' ${fiofils[i]} | awk -F "=" '{print $2}')
			c2hlat=$(getusec $c2hlat $units)
			c2hcpu=$(awk '/Average/{print 100 - $NF}' ${sarfils[i]})
			i=${i}+1
			h2cth=$(awk '/bw=/{print $3}' ${fiofils[i]} | sed 's/(//g' | sed 's/),//g') # extract bw
			unit=$(echo $h2cth | awk -F '[0-9,.]*' '{print $2}')
			value=$(echo $h2cth | sed 's/[^0-9,.]*//g')
			h2cth=$(toKB $value $unit)
			read units <<< $(awk -F " " '/clat/{print $2;exit;}' ${fiofils[i]} | awk -F "[(,)]" '{print $2}')
			h2clat=$(awk -F "," '/clat/{print $3}' ${fiofils[i]} | awk -F "=" '{print $2}')
			h2clat=$(getusec $h2clat $units)
			h2ccpu=$(awk '/Average/{print 100 - $NF}' ${sarfils[i]})
			echo $size,$h2cth,$h2clat,$h2ccpu,$c2hth,$c2hlat,$c2hcpu >> $filename
		done
	else
		for ((i=0; i<$length; i++))
		do
			size=$(echo "${fiofils[i]}" | awk -F'[_]' '{print $2}')
			#size=$(numfmt --to=iec-i --suffix=B --padding=7 $size)
			size=$(echo "scale=4; $size/1024" | bc -l)
			h2cth=$(awk '/WRITE:/{print $3}' ${fiofils[i]} | sed 's/(//g' | sed 's/),*//g')
			unit=$(echo $h2cth | awk -F '[0-9,.]*' '{print $2}')
			value=$(echo $h2cth | sed 's/[^0-9,.]*//g')
			h2cth=$(toKB $value $unit)
			c2hth=$(awk '/READ:/{print $3}' ${fiofils[i]} | sed 's/(//g' | sed 's/),//g')
			unit=$(echo $c2hth | awk -F '[0-9,.]*' '{print $2}')
			value=$(echo $c2hth | sed 's/[^0-9,.]*//g')
			c2hth=$(toKB $value $unit)
			read c2hunits h2cunits <<< $(awk -F " " '/clat/{print $2}' ${fiofils[i]} | awk -F "[(,)]" '/sec/{print $2}')
			read c2hlat h2clat <<< $(awk -F "," '/clat/{print $3}' ${fiofils[i]}| awk -F "=" '{print $2}' )
			h2clat=$(getusec $h2clat $h2cunits)
			c2hlat=$(getusec $c2hlat $c2hunits)
	
			cpu=$(awk '/Average/{print 100 - $NF}' ${sarfils[i]})
			echo $size,$h2cth,$h2clat,$cpu,$c2hth,$c2hlat,$cpu >> $filename
		done
	fi
	
	echo ' ' >>$filename
	cd -
}

cdir=$PWD
cd ${dir}
for d in */; do
	parse_dir ${dir}/$d
done
cd $cdir
