export RTE_SDK=`pwd`/../dpdk-stable-$1
export RTE_TARGET=build
meson -Denable_lua=true build
cd build
ninja
