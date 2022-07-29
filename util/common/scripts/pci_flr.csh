#!/bin/csh

# expect 1 argument of format: BUS:DEVICE:FUNCTION
# e.g. 04:00.0
if ($# != 1) then
    echo "Usage:    $0 XX:YY.ZZ"
    echo "  XX  BUS ID"
    echo "  YY  DEVICE ID"
    echo "  ZZ  FUNCTION ID"
    echo "  e.g.: $0 04:00.0"
    exit 1
endif

set dev_paths="/sys/bus/pci/devices/0000:$1"
foreach dev_path ($dev_paths) 
	echo 1 > $dev_path/reset;
end
 
