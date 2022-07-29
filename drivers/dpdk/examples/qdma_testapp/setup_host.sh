export RTE_SDK=`pwd`/../..
export RTE_TARGET=build
mkdir /mnt/huge
make clean;
rm build -rf
make
mount -t hugetlbfs -o size=4G none /mnt/huge
modprobe uio
cd ../../dpdk-kmods/linux/igb_uio
make
chmod -R 0777 igb_uio.ko
cd ${RTE_SDK}/examples/qdma_testapp
insmod ../../dpdk-kmods/linux/igb_uio/igb_uio.ko