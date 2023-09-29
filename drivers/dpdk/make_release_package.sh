major_version=2023
minor_version=2

driver_name=dpdk
append=2000-0160

copyright_script=../../util/common/scripts/copyright_header.py

usage()
{
	msg="Usage: $0 [-M <Major Version No>][-m <Minor Version No>] [-d <Driver Name>] [-a <custom append string] -h"
	echo $msg
	1>&2;
	exit 1;
}

while getopts ":M:m:d:hp:a:" o; do
	case "${o}" in
		M)
			major_version=${OPTARG}
			;;
		m)
			minor_version=${OPTARG}
			;;
		d)
			driver_name=${OPTARG}
			;;
		a)
			append=${OPTARG}
			;;
		h)
			usage
			;;
		*)
			usage
			;;
	esac
done
shift $((OPTIND-1))


version=-$major_version.$minor_version
if [ $append ];then
append=-$append
fi
release_dir=rel-$driver_name$version$append


files_2_check=(
		"RELEASE"
		"bsd_license.txt"
		"drivers/net/qdma/meson.build"
		"drivers/net/qdma/qdma.h"
		"drivers/net/qdma/qdma_common.c"
		"drivers/net/qdma/qdma_devops.c"
		"drivers/net/qdma/qdma_devops.h"
		"drivers/net/qdma/qdma_dpdk_compat.c"
		"drivers/net/qdma/qdma_dpdk_compat.h"
		"drivers/net/qdma/qdma_ethdev.c"
		"drivers/net/qdma/qdma_log.h"
		"drivers/net/qdma/qdma_mbox.c"
		"drivers/net/qdma/qdma_mbox.h"
		"drivers/net/qdma/qdma_platform.c"
		"drivers/net/qdma/qdma_platform_env.h"
		"drivers/net/qdma/qdma_rxtx.c"
		"drivers/net/qdma/qdma_rxtx.h"
		"drivers/net/qdma/qdma_user.c"
		"drivers/net/qdma/qdma_user.h"
		"drivers/net/qdma/qdma_vf_ethdev.c"
		"drivers/net/qdma/qdma_xdebug.c"
		"drivers/net/qdma/rte_pmd_qdma.c"
		"drivers/net/qdma/rte_pmd_qdma.h"
		"drivers/net/qdma/version.h"
		"drivers/net/qdma/version.map"
		"../qdma_access/eqdma_soft_access/eqdma_soft_access.c"
		"../qdma_access/eqdma_soft_access/eqdma_soft_access.h"
		"../qdma_access/eqdma_soft_access/eqdma_soft_reg.h"
		"../qdma_access/eqdma_soft_access/eqdma_soft_reg_dump.c"
		"../qdma_access/qdma_cpm4_access/qdma_cpm4_access.c"
		"../qdma_access/qdma_cpm4_access/qdma_cpm4_access.h"
		"../qdma_access/qdma_cpm4_access/qdma_cpm4_reg.h"
		"../qdma_access/qdma_cpm4_access/qdma_cpm4_reg_dump.c"
		"../qdma_access/eqdma_cpm5_access/eqdma_cpm5_access.c"
		"../qdma_access/eqdma_cpm5_access/eqdma_cpm5_access.h"
		"../qdma_access/eqdma_cpm5_access/eqdma_cpm5_reg.h"
		"../qdma_access/eqdma_cpm5_access/eqdma_cpm5_reg_dump.c"
		"../qdma_access/qdma_soft_access/qdma_soft_access.c"
		"../qdma_access/qdma_soft_access/qdma_soft_access.h"
		"../qdma_access/qdma_soft_access/qdma_soft_reg.h"
		"../qdma_access/qdma_access_common.c"
		"../qdma_access/qdma_access_common.h"
		"../qdma_access/qdma_access_errors.h"
		"../qdma_access/qdma_access_export.h"
		"../qdma_access/qdma_access_version.h"
		"../qdma_access/qdma_list.c"
		"../qdma_access/qdma_list.h"
		"../qdma_access/qdma_mbox_protocol.c"
		"../qdma_access/qdma_mbox_protocol.h"
		"../qdma_access/qdma_platform.h"
		"../qdma_access/qdma_reg_dump.h"
		"../qdma_access/qdma_resource_mgmt.c"
		"../qdma_access/qdma_resource_mgmt.h"
		"examples/qdma_testapp/Makefile"
		"examples/qdma_testapp/commands.c"
		"examples/qdma_testapp/commands.h"
		"examples/qdma_testapp/parse_obj_list.c"
		"examples/qdma_testapp/parse_obj_list.h"
		"examples/qdma_testapp/pcierw.c"
		"examples/qdma_testapp/pcierw.h"
		"examples/qdma_testapp/qdma_regs.h"
		"examples/qdma_testapp/testapp.c"
		"examples/qdma_testapp/testapp.h"
		"patches/proc-info/0001-Add-QDMA-xdebug-to-proc-info-of-dpdk-22.11.patch"
		"patches/pktgen/0001-PKTGEN-20.12.0-Patch-to-add-Jumbo-packet-support.patch"
		"patches/pktgen/0001-PKTGEN-22.04.1-Patch-to-add-Jumbo-packet-support.patch"
		"patches/pktgen/README.txt"
		"docs/README.txt"
		)

echo "Checking all files to be released are present..."
sleep 1
for fname in "${files_2_check[@]}"
do
    find $fname 1> /dev/null 2> /dev/null
    if [ $? -ne 0 ];then
	echo $fname" Not Found"
	exit
fi
done
echo "All files to be released are present..."
sleep 1

cd ../ > /dev/null
mv $release_dir $release_dir.old 1> /dev/null 2> /dev/null
mv $release_dir.zip $release_dir.old.zip 1> /dev/null 2> /dev/null
cd - > /dev/null

echo "Creating "$driver_name" Release directory..."
sleep 1

mkdir -p $(pwd)/../$release_dir
mkdir -p $(pwd)/../$release_dir/drivers
mkdir -p $(pwd)/../$release_dir/drivers/net
mkdir -p $(pwd)/../$release_dir/drivers/net/qdma
mkdir -p $(pwd)/../$release_dir/drivers/net/qdma/qdma_access
mkdir -p $(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_soft_access
mkdir -p $(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_cpm4_access
mkdir -p $(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_cpm5_access
mkdir -p $(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_soft_access
mkdir -p $(pwd)/../$release_dir/examples
mkdir -p $(pwd)/../$release_dir/examples/qdma_testapp
mkdir -p $(pwd)/../$release_dir/tools
mkdir -p $(pwd)/../$release_dir/docs

echo "Copying the release contents to "$driver_name" Release directory..."
sleep 1

cp RELEASE			$(pwd)/../$release_dir/

# Copy DPDK Driver Code
cp drivers/net/qdma/meson.build						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma.h							$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_common.c					$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_devops.c					$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_devops.h					$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_dpdk_compat.c				$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_dpdk_compat.h				$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_ethdev.c					$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_log.h						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_mbox.c						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_mbox.h						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_platform.c					$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_platform_env.h				$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_rxtx.c						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_rxtx.h						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_user.c						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_user.h						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_vf_ethdev.c				$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/qdma_xdebug.c					$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/rte_pmd_qdma.c					$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/rte_pmd_qdma.h					$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/version.h						$(pwd)/../$release_dir/drivers/net/qdma/
cp drivers/net/qdma/version.map						$(pwd)/../$release_dir/drivers/net/qdma/

# Copy QDMA Access Code
cp ../qdma_access/eqdma_soft_access/eqdma_soft_access.c		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_soft_access/
cp ../qdma_access/eqdma_soft_access/eqdma_soft_access.h		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_soft_access/
cp ../qdma_access/eqdma_soft_access/eqdma_soft_reg.h		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_soft_access/
cp ../qdma_access/eqdma_soft_access/eqdma_soft_reg_dump.c	$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_soft_access/
cp ../qdma_access/qdma_cpm4_access/qdma_cpm4_access.c		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_cpm4_access/
cp ../qdma_access/qdma_cpm4_access/qdma_cpm4_access.h		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_cpm4_access/
cp ../qdma_access/qdma_cpm4_access/qdma_cpm4_reg.h			$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_cpm4_access/
cp ../qdma_access/qdma_cpm4_access/qdma_cpm4_reg_dump.c		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_cpm4_access/
cp ../qdma_access/eqdma_cpm5_access/eqdma_cpm5_access.c		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_cpm5_access/
cp ../qdma_access/eqdma_cpm5_access/eqdma_cpm5_access.h		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_cpm5_access/
cp ../qdma_access/eqdma_cpm5_access/eqdma_cpm5_reg.h		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_cpm5_access/
cp ../qdma_access/eqdma_cpm5_access/eqdma_cpm5_reg_dump.c	$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/eqdma_cpm5_access/
cp ../qdma_access/qdma_soft_access/qdma_soft_access.c		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_soft_access/
cp ../qdma_access/qdma_soft_access/qdma_soft_access.h		$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_soft_access/
cp ../qdma_access/qdma_soft_access/qdma_soft_reg.h			$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/qdma_soft_access/
cp ../qdma_access/qdma_access_common.c						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_access_common.h						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_access_errors.h						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_access_export.h						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_access_version.h						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_list.c								$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_list.h								$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_mbox_protocol.c						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_mbox_protocol.h						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_platform.h							$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_reg_dump.h							$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_resource_mgmt.c						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/
cp ../qdma_access/qdma_resource_mgmt.h						$(pwd)/../$release_dir/drivers/net/qdma/qdma_access/

# Copy QDMA Test Application Code
cp examples/qdma_testapp/Makefile				$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/commands.c				$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/commands.h				$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/parse_obj_list.c		$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/parse_obj_list.h		$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/pcierw.c				$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/pcierw.h				$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/qdma_regs.h			$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/testapp.c				$(pwd)/../$release_dir/examples/qdma_testapp/
cp examples/qdma_testapp/testapp.h				$(pwd)/../$release_dir/examples/qdma_testapp/

# Copy tools Code
cp patches/proc-info/0001-Add-QDMA-xdebug-to-proc-info-of-dpdk-22.11.patch				$(pwd)/../$release_dir/tools/
cp patches/pktgen/0001-PKTGEN-20.12.0-Patch-to-add-Jumbo-packet-support.patch			$(pwd)/../$release_dir/tools/
cp patches/pktgen/0001-PKTGEN-22.04.1-Patch-to-add-Jumbo-packet-support.patch			$(pwd)/../$release_dir/tools/
cp patches/pktgen/README.txt			$(pwd)/../$release_dir/tools/

# Copy Docs
cp docs/README.txt						$(pwd)/../$release_dir/docs/

chmod 777 -R $(pwd)/../$release_dir/
chmod -R 0777 $(pwd)/../$release_dir/drivers/net/qdma/qdma_access
chmod -R +w $(pwd)/../$release_dir/drivers/net/qdma/qdma_access/*
python ${copyright_script} -d $(pwd)/../$release_dir/drivers/net/qdma/qdma_access -c bsd_license.txt -a -f > /dev/null

cd .. > /dev/null
echo "Preparing release ZIP Package"
sleep 1
zip -r $release_dir.zip $release_dir > /dev/null
if [ $? -ne 0 ];then
	echo "ZIP Creation Failed"
	exit
fi
file_path=$(pwd)"/"$release_dir".zip"
cd - > /dev/null
abspath=$(realpath --relative-to=$(pwd) $file_path)
echo $driver_name" Package Prepared Successfully @"$abspath
sleep 1
