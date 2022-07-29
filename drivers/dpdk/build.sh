meson build
cd build
ninja
ninja install
ldconfig
cd ../dpdk-kmods/linux/igb_uio
make
chmod 777 igb_uio.ko
cd ../../../