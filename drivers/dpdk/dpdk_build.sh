#!/bin/sh

# Cause shell to exit on an error

#set -e
checkpach_mandate=1
exit_on_cp_errs=1
extract_sources=1

checkpatch=$1/HEAD/proj/util/common/checkpatch/checkpatch.pl

function print_errs() {
	while read -r line; do
		echo $line
	done <<< "$1"
}

function run_checkpatch() {
	chmod +x ${checkpatch}
	echo "Running checkpatch"

	${checkpatch} --no-tree -f --show-types --ignore=OOM_MESSAGE,LINUX_VERSION_CODE,FILE_PATH_CHANGES,VOLATILE,PREFER_PACKED,PREFER_ALIGNED,PREFER_PRINTF,PREFER_KERNEL_TYPES,BIT_MACRO,CONST_STRUCT,SPLIT_STRING,LONG_LINE_STRING,LINE_SPACING,PARENTHESIS_ALIGNMENT,NETWORKING_BLOCK_COMMENT_STYLE,NEW_TYPEDEFS,COMPARISON_TO_NULL  $PWD/drivers/net/qdma/* > $PWD/drivers/net/qdma/tmp_cp_log

	cp_errs=$(cat $PWD/drivers/net/qdma/tmp_cp_log | grep "ERROR\|WARNING\|FILE ")
	rm -f $PWD/drivers/net/qdma/tmp_cp_log

	if [ "${cp_errs}" != "" ]; then
		echo "-------------------"
		echo "Checkpatch Errors:"
		echo "-------------------"
		print_errs "${cp_errs}"
		if [ ${exit_on_cp_errs} -ne 0 ]; then
			echo ""
			echo -e "\033[1m***CLEAR CHECKPATCH ERRORS TO CONTINUE***\033[0m"
			echo ""
			exit 1
		fi
	fi

}
function run_checkpatch_access() {
	chmod +x ${checkpatch}
	echo "Running checkpatch on qdma_access code"

	${checkpatch} --no-tree -f --show-types --ignore=OOM_MESSAGE,LINUX_VERSION_CODE,FILE_PATH_CHANGES,VOLATILE,PREFER_PACKED,PREFER_ALIGNED,PREFER_PRINTF,PREFER_KERNEL_TYPES,BIT_MACRO,CONST_STRUCT,SPLIT_STRING,LONG_LINE_STRING,LINE_SPACING,PARENTHESIS_ALIGNMENT,NETWORKING_BLOCK_COMMENT_STYLE,NEW_TYPEDEFS,COMPARISON_TO_NULL  $PWD/drivers/net/qdma/qdma_access/* > $PWD/drivers/net/qdma/qdma_access/tmp_cp_log

	cp_errs=$(cat $PWD/drivers/net/qdma/qdma_access/tmp_cp_log | grep "ERROR\|WARNING\|FILE ")
	rm -f $PWD/drivers/net/qdma/qdma_access/tmp_cp_log

	if [ "${cp_errs}" != "" ]; then
		echo "-------------------"
		echo "Checkpatch Errors:"
		echo "-------------------"
		print_errs "${cp_errs}"
		if [ ${exit_on_cp_errs} -ne 0 ]; then
			echo ""
			echo -e "\033[1m***CLEAR CHECKPATCH ERRORS TO CONTINUE***\033[0m"
			echo ""
			exit 1
		fi
	fi
}

if [ ${extract_sources} -ne 0 ]; then
	cp $1/HEAD/incoming/dpdk/dpdk-sources/dpdk-stable-19.11.tar.gz .
	if [ -d "dpdk-stable-19.11" ]; then
		rm -rf dpdk-stable-19.11
	fi
	tar -xvf dpdk-stable-19.11.tar.gz
fi

if [ -d "dpdk-stable-19.11" ]; then
	cd dpdk-stable-19.11/
else
	echo -e "dpdk-stable-19.11 directory does not exist, try enabling 'extract_sources' flag in script"
	echo ""
	exit 1
fi

if [ ! -d "drivers/net/qdma/" ]; then
	mkdir drivers/net/qdma/
fi

rm -rf build/
cp -fr $1/HEAD/proj/sw_host/dpdk/drivers/net/qdma/* drivers/net/qdma/.

if [ -d "drivers/net/qdma/qdma_access/" ]; then
	rm -rf drivers/net/qdma/qdma_access/
fi

if [ ${checkpach_mandate} -ne 0 ]; then
		run_checkpatch
fi

cp -fr $1/HEAD/proj/sw_host/qdma_access/ drivers/net/qdma/.

if [ ${checkpach_mandate} -ne 0 ]; then
		run_checkpatch_access
fi
chmod +rw drivers/net/qdma/qdma_access/
python $1/HEAD/proj/util/common/scripts/copyright_header.py -d drivers/net/qdma/qdma_access/ -c $1/HEAD/proj/sw_host/dpdk/bsd_license.txt -a -f

if [ ${extract_sources} -ne 0 ]; then
	cp $1/HEAD/proj/sw_host/dpdk/patches/dpdk/0001-net-qdma-Integrate-qdma-pmd-to-dpdk-19.11.patch .
	patch -p1 < 0001-net-qdma-Integrate-qdma-pmd-to-dpdk-19.11.patch
fi
make config T=x86_64-native-linuxapp-gcc
make -j32
