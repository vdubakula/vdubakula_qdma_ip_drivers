echo "dpdk bind driver used for vfs"
cmd=`lspci | grep -i xilinx | awk -F " " '(($7 > "a000" && $7< "b000") || ($7 > "c000" && $7 < "d000")){print $1}' | tr -t "\n" " "`
../../usertools/dpdk-devbind.py -b igb_uio $cmd
