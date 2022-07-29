num_pfs=4
num_vfs=8
pci_bbddf=81000
bind_drv=igb_uio

if [ ! -z $1 ]; then
	bind_drv=$1
fi

if [ ! -z $2 ]; then
	pci_bbddf=$2
fi

if [ ! -z $3 ]; then
	num_vfs=$3
fi

pci_bus=${pci_bbddf:0:2}
pci_device=${pci_bbddf:2:2}

for ((i = 0; i < num_pfs; i++))
do
	../../usertools/dpdk-devbind.py -b igb_uio ${pci_bus}:${pci_device}.${i}
	if [ $? -lt 0 ]; then
		echo "failed to bind pf[${i}]"
		exit 1
	fi
	echo $num_vfs > /sys/bus/pci/devices/0000\:${pci_bus}\:${pci_device}.${i}/max_vfs
done

if [ "$bind_drv" = "vfio-pci" ]; then

	for ((i = 0; i < num_pfs; i++))
	do
		../../usertools/dpdk-devbind.py -u ${pci_bus}:${pci_device}.${i}
		../../usertools/dpdk-devbind.py -b $bind_drv ${pci_bus}:${pci_device}.${i}
		if [ $? -lt 0 ]; then
			echo "failed to bind pf[${i}]"
			exit 1
		fi
	done
fi

echo "dpdk bind driver used for vfs: "$bind_drv

cmd=`lspci | grep -i xilinx | awk -F " " '$7 > "a000" {print $1}' | tr -t "\n" " "`
../../usertools/dpdk-devbind.py -b $bind_drv $cmd
if [ $? -lt 0 ]; then
	echo "failed to bind vfs"
	exit 1
fi


