#!/bin/sh
usrbarctrl=$(($2 + 0x8))
usrbarmarkerstatus=$(($2 + 0x18))
is_eqdma=$3
echo $usrbarctrl $usrbarmarkerstatus
echo "is_eqdma is $is_eqdma"
if(( $is_eqdma==1 ))
then
	# Setting the marker
	./PCIeWriter/rwmem $usrbarctrl 0x120020
	retry=0
	while [ $retry -le 50 ]
	do
		sleep 2
		status_reg=`./PCIeWriter/rwmem $(($usrbarmarkerstatus))`
		status_reg=`echo $status_reg | sed 's/.*= 0x*\([a-z0-9]*\).*/\1/'`
		status_reg="0x$status_reg"
		echo "status_reg is $status_reg"
		cmpt_status=$(( status_reg&0x1 ))
		echo "cmpt_status is $cmpt_status"
		if (( $cmpt_status==1 ))
		then
			break
		fi
		retry=$((retry + 1))
	done
	if (( $cmpt_status!=1 ))
	then
		echo "C2H Marker completion is not received"
	fi
fi



