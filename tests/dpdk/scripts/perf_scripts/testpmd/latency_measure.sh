# Set Window Size to 1s
./PCIeWriter/rwmem $(($1 + 0x100)) 0x0
# Reset
./PCIeWriter/rwmem $(($1 + 0x108)) 3
# Reset
./PCIeWriter/rwmem $(($1 + 0x108)) 2
sleep 2
# Set Window Size to 1s
./PCIeWriter/rwmem $(($1 + 0x100)) 0xee6b280
# Reset
./PCIeWriter/rwmem $(($1 + 0x108)) 3
# Reset
./PCIeWriter/rwmem $(($1 + 0x108)) 2
sleep 2
# Free Counter
free_cntr=`./PCIeWriter/rwmem $(($1 + 0x10C))`
free_cntr=`echo $free_cntr | sed 's/.*= 0x*\([a-z0-9]*\).*/\1/'`
free_cntr=$(( 16#$free_cntr ))

# Idle Counter
idle_cntr=`./PCIeWriter/rwmem $(($1 + 0x114))`
idle_cntr=`echo $idle_cntr | sed 's/.*= 0x*\([a-z0-9]*\).*/\1/'`
idle_cntr=$(( 16#$idle_cntr ))

# Busy Counter
busy_cntr=`./PCIeWriter/rwmem $(($1 + 0x11C))`
busy_cntr=`echo $busy_cntr | sed 's/.*= 0x*\([a-z0-9]*\).*/\1/'`
busy_cntr=$(( 16#$busy_cntr ))
#printf "Busy:   $busy_cntr  \n"

# Busy Counter
busy2_cntr=`./PCIeWriter/rwmem $(($1 + 0x120))`
busy2_cntr=`echo $busy2_cntr | sed 's/.*= 0x*\([a-z0-9]*\).*/\1/'`
busy2_cntr=$(( 16#$busy2_cntr ))
#printf "Busy2:   $busy2_cntr  \n"

# Active Counter
active_cntr=`./PCIeWriter/rwmem $(($1 + 0x124))`
active_cntr=`echo $active_cntr | sed 's/.*= 0x*\([a-z0-9]*\).*/\1/'`
active_cntr=$(( 16#$active_cntr ))

busy2_cntr=$(($busy2_cntr<<32))
busy2_cntr=$(($busy2_cntr+$busy_cntr))
#printf "T-Busy2:   $busy2_cntr  \n"
max_lat=`bc -l <<<"($free_cntr)*4/1000"`
min_lat=`bc -l <<<"($idle_cntr)*4/1000"`
active_percent=`bc -l <<<"($busy2_cntr)/$active_cntr"`
avg_lat=`bc -l <<<"($active_percent)*4/1000"`

printf "MAX Latency:   $free_cntr  cylces %.3f micro-sec\n" "$max_lat"
printf "Min latency:   $idle_cntr  cylces %.3f micro-sec\n" "$min_lat"
printf "total packets : $active_cntr \n"
printf "Average Latency:  %.3f cycles %.3f  micro-sec\n" "$active_percent" "$avg_lat"
