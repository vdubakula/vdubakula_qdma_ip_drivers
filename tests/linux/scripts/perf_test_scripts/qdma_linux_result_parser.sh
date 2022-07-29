#!/bin/bash

#set -x
if [ $# -gt 1 ];then
	echo "Usage: $0 <full path of directory>" 
	exit 1
fi
dir=$1

if [[ ! -d $dir ]];then
	echo "Directory $dir does not exist"
	exit 1
fi

toMb()
{
local value=$1
local unit=$2
if [[ "$unit" == "KB/sec" ]];then
	echo "$(echo "scale=4; ($value*8)/1000" | bc -l)"
elif [[ "$unit" == "MB/sec" ]];then
	echo "$(echo "scale=4; $value*8" | bc -l)"
elif [[ "$unit" == "GB/sec" ]];then
	echo "$(echo "scale=4; $value*1000*8" | bc -l)"
else
	echo "$(echo "scale=4; ($value*8)/1000000" | bc -l)"
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
	readarray fiofils < <(find . -type f -name "log*" | sort -k 2 -t _ -g)
	readarray sarfils < <(find . -type f -name "sar*" | sort -k 2 -t _ -g)
	
	echo $resdir >> $filename
	echo "iosize(KiB)"," ","H2C"," "," ","C2H" >> $filename
	echo " ","throughput(Mb/s)","pps","CPU%","throughput(Mb/s)","pps","CPU%">>$filename
	
	length=${#fiofils[@]}
	
	if [[ "$direc" == "unidir" ]];then
		for ((i=0; i<$length; i++))
		do
			size=$(echo "${fiofils[i]}" | awk -F'[_.]' '{print $3}')  #extract io size from file name
			size=$(echo "scale=4; $size" | bc -l) #convert io size to kB
			_filename=${fiofils[i]}
			if [[ $_filename = *c2h* ]]; then
					c2hth=$(awk '/READ:/{print $8}' ${fiofils[i]}) # extract bw
				unit=$(awk '/READ:/{print $9}' ${fiofils[i]}) #extract bw unit
				value=$(echo $c2hth | sed 's/[^0-9,.]*//g') #extract bw value
				c2hth=$(toMb $value $unit) #calculate in kiB
				c2hpps=$(awk '/READ:/{print $5}' ${fiofils[i]})
				c2hcpu=$(awk '/Average:/ && $2 ~ /all/ {print $5}' ${sarfils[i]})
				i=$((i+1))
			else
				c2hcpu=
				c2hpps=
				c2hth=
			fi
			_filename=${fiofils[i]}
			if [[ $_filename = *h2c* ]]; then
				h2cth=$(awk '/WRITE:/{print $8}' ${fiofils[i]}) # extract bw
				unit=$(awk '/WRITE:/{print $9}' ${fiofils[i]})
				value=$(echo $h2cth | sed 's/[^0-9,.]*//g')
				h2cth=$(toMb $value $unit)
				h2cpps=$(awk '/WRITE:/{print $5}' ${fiofils[i]})
				h2ccpu=$(awk '/Average:/ && $2 ~ /all/ {print $5}' ${sarfils[i]})
			else
				i=$((i-1))
				h2ccpu=
				h2cppc=
				h2cth=
			fi
			echo $size,$h2cth,$h2cpps,$h2ccpu,$c2hth,$c2hpps,$c2hcpu >> $filename

		done
	else
		for ((i=0; i<$length; i++))
		do
			size=$(echo "${fiofils[i]}" | awk -F'[_]' '{print $2}')
			size=$(echo "scale=4; $size" | bc -l)
			h2cth=$(awk '/WRITE:/{print $8}' ${fiofils[i]}) # extract bw
			unit=$(awk '/WRITE:/{print $9}' ${fiofils[i]})
			value=$(echo $h2cth | sed 's/[^0-9,.]*//g')
			h2cth=$(toMb $value $unit)
			h2cpps=$(awk '/WRITE:/{print $5}' ${fiofils[i]})
			c2hth=$(awk '/READ:/{print $8}' ${fiofils[i]}) # extract bw
			unit=$(awk '/READ:/{print $9}' ${fiofils[i]}) #extract bw unit
			value=$(echo $c2hth | sed 's/[^0-9,.]*//g')
			c2hth=$(toMb $value $unit)
			c2hpps=$(awk '/READ:/{print $5}' ${fiofils[i]})
			c2hcpu=$(awk '/Average:/ && $2 ~ /all/ {print $5}' ${sarfils[i]})
			h2ccpu=$c2hcpu
			echo $size,$h2cth,$h2cpps,$h2ccpu,$c2hth,$c2hpps,$c2hcpu >> $filename
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
