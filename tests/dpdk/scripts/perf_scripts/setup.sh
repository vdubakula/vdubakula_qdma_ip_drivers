export RTE_SDK=`pwd`/../..
export RTE_TARGET=build
mkdir /mnt/huge
mount -t hugetlbfs nodev /mnt/huge
modprobe uio
cd ${RTE_SDK}/dpdk-kmods/linux/igb_uio
make
chmod -R 0777 igb_uio.ko
cd ${RTE_SDK}/perf_scripts/testpmd
insmod ${RTE_SDK}/dpdk-kmods/linux/igb_uio/igb_uio.ko
