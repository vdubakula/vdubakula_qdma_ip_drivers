major_version=2022
minor_version=1

driver_name=linux
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
		"apps/dma-ctl/cmd_parse.c"
		"apps/dma-ctl/cmd_parse.h"
		"apps/dma-ctl/main.c"
		"apps/dma-ctl/Makefile"
		"apps/dma-ctl/version.h"
		"apps/dma-from-device/dma_from_device.c"
		"apps/dma-from-device/Makefile"
		"apps/dma-from-device/version.h"
		"apps/dma-latency/dmalat.c"
		"apps/dma-latency/Makefile"
		"apps/dma-latency/Readme.txt"
		"apps/dma-latency/sample_dma_latency_config.txt"
		"apps/dma-latency/version.h"
		"apps/dma-perf/dmaperf.c"
		"apps/dma-perf/Makefile"
		"apps/dma-perf/version.h"
		"apps/dma-to-device/dma_to_device.c"
		"apps/dma-to-device/Makefile"
		"apps/dma-to-device/version.h"
		"apps/dma-utils/dmactl.c"
		"apps/dma-utils/dmactl_internal.h"
		"apps/dma-utils/dmactl_reg.c"
		"apps/dma-utils/dmautils.c"
		"apps/dma-utils/dmautils.h"
		"apps/dma-utils/dmaxfer.c"
		"apps/dma-utils/dmaxfer.h"
		"apps/dma-utils/dma_xfer_utils.c"
		"apps/dma-utils/Makefile"
		"apps/dma-utils/version.h"
		"apps/dma-xfer/dmaxfer.c"
		"apps/dma-xfer/Makefile"
		"apps/dma-xfer/sample_qdma_xfer_config.txt"
		"apps/dma-xfer/version.h"
		"apps/Makefile"
		"bsd_license.txt"
		"COPYING"
		"docs/dma-ctl.8.gz"
		"docs/README"
		"driver/include/qdma_nl.h"
		"driver/include/qdma_user_reg_dump.h"
		"driver/include/xdev_regs.h"
		"driver/libqdma/libqdma_config.c"
		"driver/libqdma/qdma_descq.h"
		"driver/libqdma/qdma_mbox.c"
		"driver/libqdma/qdma_st_c2h.c"
		"driver/libqdma/version.h"
		"driver/libqdma/libqdma_config.h"
		"driver/libqdma/Makefile"
		"driver/libqdma/qdma_debugfs.c"
		"driver/libqdma/qdma_debugfs_queue.c"
		"driver/libqdma/qdma_intr.c"
		"driver/libqdma/qdma_mbox.h"
		"driver/libqdma/qdma_regs.c"
		"driver/libqdma/qdma_st_c2h.h"
		"driver/libqdma/qdma_ul_ext.h"
		"driver/libqdma/xdev.c"
		"driver/libqdma/qdma_debugfs_dev.c"
		"driver/libqdma/qdma_debugfs_queue.h"
		"driver/libqdma/qdma_intr.h"
		"driver/libqdma/qdma_regs.h"
		"driver/libqdma/thread.c"
		"driver/libqdma/xdev.h"
		"driver/libqdma/libqdma_export.c"
		"driver/libqdma/qdma_compat.h"
		"driver/libqdma/qdma_debugfs_dev.h"
		"driver/libqdma/qdma_device.c"
		"driver/libqdma/qdma_platform.c"
		"driver/libqdma/qdma_thread.c"
		"driver/libqdma/thread.h"
		"driver/libqdma/libqdma_export.h"
		"driver/libqdma/qdma_context.c"
		"driver/libqdma/qdma_device.h"
		"driver/libqdma/qdma_platform_env.h"
		"driver/libqdma/qdma_sriov.c"
		"driver/libqdma/qdma_thread.h"
		"driver/libqdma/qdma_context.h"
		"driver/libqdma/qdma_debugfs.h"
		"driver/libqdma/qdma_descq.c"
		"driver/libqdma/qdma_license.h"
		"driver/Makefile"
		"driver/make_rules/common_flags.mk"
		"driver/make_rules/distro_check.mk"
		"driver/make_rules/kernel_check.mk"
		"driver/src/cdev.c"
		"driver/src/Makefile"
		"driver/src/nl.h"
		"driver/src/pci_ids.h"
		"driver/src/qdma_mod.h"
		"driver/src/cdev.h"
		"driver/src/nl.c"
		"driver/src/qdma_mod.c"
		"driver/src/version.h"
		"LICENSE"
		"license.txt"
		"Makefile"
		"RELEASE"
		"scripts/datafile_16bit_pattern.bin"
		"scripts/license-for-datafile_16bit_pattern.txt"
		"scripts/qdma_generate_conf_file.sh"
		"scripts/qdma_run_test_mm_vf.sh"
		"scripts/qdma_run_test_pf.sh"
		"scripts/qdma_run_test_st_vf.sh"
		"scripts/qdma_vf_auto_tst.sh"
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
mkdir -p $(pwd)/../$release_dir/apps
mkdir -p $(pwd)/../$release_dir/apps/dma-ctl
mkdir -p $(pwd)/../$release_dir/apps/dma-from-device
mkdir -p $(pwd)/../$release_dir/apps/dma-latency
mkdir -p $(pwd)/../$release_dir/apps/dma-perf
mkdir -p $(pwd)/../$release_dir/apps/dma-to-device
mkdir -p $(pwd)/../$release_dir/apps/dma-utils
mkdir -p $(pwd)/../$release_dir/apps/dma-xfer
mkdir -p $(pwd)/../$release_dir/apps/include
mkdir -p $(pwd)/../$release_dir/docs
mkdir -p $(pwd)/../$release_dir/driver
mkdir -p $(pwd)/../$release_dir/driver/include
mkdir -p $(pwd)/../$release_dir/driver/libqdma
mkdir -p $(pwd)/../$release_dir/driver/libqdma/qdma_access
mkdir -p $(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_soft_access
mkdir -p $(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_cpm4_access
mkdir -p $(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_cpm5_access
mkdir -p $(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_soft_access
mkdir -p $(pwd)/../$release_dir/driver/make_rules
mkdir -p $(pwd)/../$release_dir/driver/src
mkdir -p $(pwd)/../$release_dir/scripts


echo "Copying the release contents to "$driver_name" Release directory..."
sleep 1


# Copy apps
cp apps/dma-ctl/cmd_parse.c								    $(pwd)/../$release_dir/apps/dma-ctl/
cp apps/dma-ctl/cmd_parse.h								    $(pwd)/../$release_dir/apps/dma-ctl/
cp apps/dma-ctl/main.c									    $(pwd)/../$release_dir/apps/dma-ctl/
cp apps/dma-ctl/Makefile								    $(pwd)/../$release_dir/apps/dma-ctl/
cp apps/dma-ctl/version.h								    $(pwd)/../$release_dir/apps/dma-ctl/
cp apps/dma-from-device/dma_from_device.c				    $(pwd)/../$release_dir/apps/dma-from-device/
cp apps/dma-from-device/Makefile						    $(pwd)/../$release_dir/apps/dma-from-device/
cp apps/dma-from-device/version.h						    $(pwd)/../$release_dir/apps/dma-from-device/
cp apps/dma-latency/dmalat.c							    $(pwd)/../$release_dir/apps/dma-latency/
cp apps/dma-latency/Makefile							    $(pwd)/../$release_dir/apps/dma-latency/
cp apps/dma-latency/Readme.txt							    $(pwd)/../$release_dir/apps/dma-latency/
cp apps/dma-latency/sample_dma_latency_config.txt		    $(pwd)/../$release_dir/apps/dma-latency/
cp apps/dma-latency/version.h							    $(pwd)/../$release_dir/apps/dma-latency/
cp apps/dma-perf/dmaperf.c								    $(pwd)/../$release_dir/apps/dma-perf/
cp apps/dma-perf/Makefile								    $(pwd)/../$release_dir/apps/dma-perf/
cp apps/dma-perf/version.h								    $(pwd)/../$release_dir/apps/dma-perf/
cp apps/dma-to-device/dma_to_device.c					    $(pwd)/../$release_dir/apps/dma-to-device/
cp apps/dma-to-device/Makefile							    $(pwd)/../$release_dir/apps/dma-to-device/
cp apps/dma-to-device/version.h								$(pwd)/../$release_dir/apps/dma-to-device/
cp apps/dma-utils/dmactl.c									$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/dmactl_internal.h							$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/dmactl_reg.c								$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/dmautils.c								$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/dmautils.h								$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/dmaxfer.c									$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/dmaxfer.h									$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/dma_xfer_utils.c							$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/Makefile									$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-utils/version.h									$(pwd)/../$release_dir/apps/dma-utils/
cp apps/dma-xfer/dmaxfer.c									$(pwd)/../$release_dir/apps/dma-xfer/
cp apps/dma-xfer/Makefile									$(pwd)/../$release_dir/apps/dma-xfer/
cp apps/dma-xfer/sample_qdma_xfer_config.txt				$(pwd)/../$release_dir/apps/dma-xfer/
cp apps/dma-xfer/version.h									$(pwd)/../$release_dir/apps/dma-xfer/
cp apps/Makefile											$(pwd)/../$release_dir/apps/

cp driver/include/qdma_nl.h									$(pwd)/../$release_dir/apps/include/
cp driver/include/qdma_user_reg_dump.h						$(pwd)/../$release_dir/apps/include/
cp driver/include/xdev_regs.h								$(pwd)/../$release_dir/apps/include/

cp bsd_license.txt											$(pwd)/../$release_dir/
cp COPYING													$(pwd)/../$release_dir/

# Copy Docs
cp docs/dma-ctl.8.gz										$(pwd)/../$release_dir/docs/
cp docs/README												$(pwd)/../$release_dir/docs/

# Copy Driver
cp driver/include/qdma_nl.h									$(pwd)/../$release_dir/driver/include/
cp driver/include/qdma_user_reg_dump.h						$(pwd)/../$release_dir/driver/include/
cp driver/include/xdev_regs.h								$(pwd)/../$release_dir/driver/include/
cp driver/libqdma/libqdma_config.c							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_descq.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_mbox.c								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_st_c2h.c								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/version.h									$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/libqdma_config.h							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/Makefile									$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_debugfs.c							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_debugfs_queue.c						$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_intr.c								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_mbox.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_regs.c								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_st_c2h.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_ul_ext.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/xdev.c									$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_debugfs_dev.c						$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_debugfs_queue.h						$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_intr.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_regs.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/thread.c									$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/xdev.h									$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/libqdma_export.c							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_compat.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_debugfs_dev.h						$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_device.c								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_platform.c							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_thread.c								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/thread.h									$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/libqdma_export.h							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_context.c							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_device.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_platform_env.h						$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_sriov.c								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_thread.h								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_context.h							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_debugfs.h							$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_descq.c								$(pwd)/../$release_dir/driver/libqdma/
cp driver/libqdma/qdma_license.h							$(pwd)/../$release_dir/driver/libqdma/
cp driver/Makefile											$(pwd)/../$release_dir/driver/
cp driver/make_rules/common_flags.mk 						$(pwd)/../$release_dir/driver/make_rules/
cp driver/make_rules/distro_check.mk 						$(pwd)/../$release_dir/driver/make_rules/
cp driver/make_rules/kernel_check.mk 						$(pwd)/../$release_dir/driver/make_rules/
cp driver/src/cdev.c 										$(pwd)/../$release_dir/driver/src/
cp driver/src/Makefile 										$(pwd)/../$release_dir/driver/src/
cp driver/src/pci_ids.h 									$(pwd)/../$release_dir/driver/src/
cp driver/src/nl.h 											$(pwd)/../$release_dir/driver/src/
cp driver/src/qdma_mod.h 									$(pwd)/../$release_dir/driver/src/
cp driver/src/cdev.h 										$(pwd)/../$release_dir/driver/src/
cp driver/src/nl.c 											$(pwd)/../$release_dir/driver/src/
cp driver/src/qdma_mod.c 									$(pwd)/../$release_dir/driver/src/
cp driver/src/version.h 									$(pwd)/../$release_dir/driver/src/
cp LICENSE													$(pwd)/../$release_dir/
cp license.txt												$(pwd)/../$release_dir/
cp Makefile													$(pwd)/../$release_dir/
cp RELEASE													$(pwd)/../$release_dir/

# Copy Scripts
cp scripts/datafile_16bit_pattern.bin						$(pwd)/../$release_dir/scripts/
cp scripts/license-for-datafile_16bit_pattern.txt			$(pwd)/../$release_dir/scripts/
cp scripts/qdma_generate_conf_file.sh						$(pwd)/../$release_dir/scripts/
cp scripts/qdma_run_test_mm_vf.sh							$(pwd)/../$release_dir/scripts/
cp scripts/qdma_run_test_pf.sh								$(pwd)/../$release_dir/scripts/
cp scripts/qdma_run_test_st_vf.sh							$(pwd)/../$release_dir/scripts/
cp scripts/qdma_vf_auto_tst.sh								$(pwd)/../$release_dir/scripts/

# Copy qdma_access
cp ../qdma_access/eqdma_soft_access/eqdma_soft_access.c		$(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_soft_access/
cp ../qdma_access/eqdma_soft_access/eqdma_soft_access.h		$(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_soft_access/
cp ../qdma_access/eqdma_soft_access/eqdma_soft_reg.h		$(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_soft_access/
cp ../qdma_access/eqdma_soft_access/eqdma_soft_reg_dump.c	$(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_soft_access/
cp ../qdma_access/qdma_cpm4_access/qdma_cpm4_access.c		$(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_cpm4_access/
cp ../qdma_access/qdma_cpm4_access/qdma_cpm4_access.h		$(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_cpm4_access/
cp ../qdma_access/qdma_cpm4_access/qdma_cpm4_reg.h			$(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_cpm4_access/
cp ../qdma_access/qdma_cpm4_access/qdma_cpm4_reg_dump.c		$(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_cpm4_access/
cp ../qdma_access/eqdma_cpm5_access/eqdma_cpm5_access.c		$(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_cpm5_access/
cp ../qdma_access/eqdma_cpm5_access/eqdma_cpm5_access.h		$(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_cpm5_access/
cp ../qdma_access/eqdma_cpm5_access/eqdma_cpm5_reg.h		$(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_cpm5_access/
cp ../qdma_access/eqdma_cpm5_access/eqdma_cpm5_reg_dump.c	$(pwd)/../$release_dir/driver/libqdma/qdma_access/eqdma_cpm5_access/
cp ../qdma_access/qdma_soft_access/qdma_soft_access.c		$(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_soft_access/
cp ../qdma_access/qdma_soft_access/qdma_soft_access.h		$(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_soft_access/
cp ../qdma_access/qdma_soft_access/qdma_soft_reg.h			$(pwd)/../$release_dir/driver/libqdma/qdma_access/qdma_soft_access/
cp ../qdma_access/qdma_access_common.c						$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_access_common.h						$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_access_errors.h						$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_access_export.h						$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_access_version.h						$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_list.c								$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_list.h								$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_mbox_protocol.c						$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_mbox_protocol.h						$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_platform.h							$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_reg_dump.h							$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_resource_mgmt.c						$(pwd)/../$release_dir/driver/libqdma/qdma_access/
cp ../qdma_access/qdma_resource_mgmt.h						$(pwd)/../$release_dir/driver/libqdma/qdma_access/



chmod 777 -R $(pwd)/../$release_dir/

echo "Updating the license header for qdma_access..."
chmod -R 0777 $(pwd)/../$release_dir/driver/libqdma/qdma_access
chmod -R +w $(pwd)/../$release_dir/driver/libqdma/qdma_access/*
python ${copyright_script} -d $(pwd)/../$release_dir/driver/libqdma/qdma_access -c license.txt -a -f > /dev/null


echo "Updating the license header for apps/include"
chmod -R 0777 $(pwd)/../$release_dir/apps/include
chmod -R +w $(pwd)/../$release_dir/apps/include/*
python ${copyright_script} -d $(pwd)/../$release_dir/apps/include/ -c bsd_license.txt -f > /dev/null



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

