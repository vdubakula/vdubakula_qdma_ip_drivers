#!/bin/bash

pmd_dir=$1
testapp_dir=$2
compile_flags=$3

pmd_coverity_errors_orig="4270"
testapp_coverity_errors_orig="42"

echo "Static Analysis Run"
git config --global user.name "cadman"
git config --global user.email cadman@xilinx.com
checkpatch=../../../util/common/checkpatch/checkpatch.pl
dpdk_code_path=../drivers/net/qdma/*
qdma_access_code_path=../../qdma_access/*
qdma_testapp_code_path=../examples/qdma_testapp/*

echo "Static Analysis Run: Checkpatch"
cd ${pmd_dir}
chmod +x ${checkpatch}
${checkpatch} --no-tree -f --show-types --ignore LINUX_VERSION_CODE,VOLATILE,PREFER_PACKED,PREFER_ALIGNED,PREFER_PRINTF,PREFER_KERNEL_TYPES,BIT_MACRO,CONST_STRUCT,SPLIT_STRING,LONG_LINE_STRING,LINE_SPACING,PARENTHESIS_ALIGNMENT,NETWORKING_BLOCK_COMMENT_STYLE,NEW_TYPEDEFS,COMPARISON_TO_NULL ${dpdk_code_path} ${qdma_access_code_path} ${qdma_testapp_code_path} > dpdk_checkpatch_log.txt
cp_errs=$(cat dpdk_checkpatch_log.txt | grep "ERROR\|WARNING\|FILE")
if [ "${cp_errs}" != "" ]; then
	echo "-------------------"
	echo "Checkpatch Errors:"
	echo "-------------------"
	echo "${cp_errs}"
	echo ""
	echo -e "\033[1m***CLEAR CHECKPATCH ERRORS TO CONTINUE***\033[0m"
	echo ""
	exit 1
fi

echo "Static Analysis Run: dpdk driver cppchecker"
cd "${pmd_dir}/drivers/net/qdma"
if [ ! -f "../../../../../../util/dpdk/cppchecker/cppchecker_avoided_errors.txt" ]; then
	echo -e "\033[1m***ERROR KNOWN ERROR FILE NOT PRESENT***\033[0m"
	echo ""
	exit 1
fi

rm dpdk_cppchecker_errors.txt dpdk_cppchecker_err.txt dpdk_cppchecker_err_orig.txt
cppcheck --suppress=variableScope --enable=all -DBIT -DBITS_PER_BYTE -DBITS_PER_LONG -DBITS_PER_LONG_LONG -DCHAR_BIT -DGENMASK -DGENMASK_ULL -DGENL_ID_GENERATE -DARRAY_SIZE --inconclusive --force . 2> dpdk_cppchecker_err.txt
cp dpdk_cppchecker_err.txt dpdk_cppchecker_err_orig.txt
sed  -i 's/:[0-9]*/:/' dpdk_cppchecker_err.txt
diff -uh ../../../../../../util/dpdk/cppchecker/cppchecker_avoided_errors.txt dpdk_cppchecker_err.txt | egrep '^\\+' | egrep -v \'^\+\+\' > dpdk_cppchecker_errors.txt
read cpperr <<< $( wc -l dpdk_cppchecker_errors.txt | awk '{ print $1 }' )
if [ -z $cpperr > 0 ]; then
	echo -e "\033[1m*** $cpperr New errors found by cppchecker***\033[0m"
	echo -e "\033[1m***CLEAR CPPCHECKER ERRORS TO CONTINUE***\033[0m"
	cat dpdk_cppchecker_errors.txt
	exit 1
fi

echo "Static Analysis Run: dpdk testapp cppchecker"
cd `pwd`/../../../examples/qdma_testapp
rm testapp_cppchecker_errors.txt testapp_cppchecker_err.txt testapp_cppchecker_err_orig.txt
cppcheck --suppress=variableScope --enable=all -DBIT -DBITS_PER_BYTE -DBITS_PER_LONG -DBITS_PER_LONG_LONG -DCHAR_BIT -DGENMASK -DGENMASK_ULL -DGENL_ID_GENERATE -DARRAY_SIZE --inconclusive --force . 2> testapp_cppchecker_err.txt
cp testapp_cppchecker_err.txt testapp_cppchecker_err_orig.txt
sed  -i 's/:[0-9]*/:/' testapp_cppchecker_err.txt
diff -uh ../../../../../util/dpdk/cppchecker/cppchecker_avoided_errors.txt testapp_cppchecker_err.txt | egrep '^\\+' | egrep -v \'^\+\+\' > testapp_cppchecker_errors.txt
read cpperr <<< $( wc -l testapp_cppchecker_errors.txt | awk '{ print $1 }' )
if [ -z $cpperr > 0 ]; then
	echo -e "\033[1m*** $cpperr New errors found by cppchecker***\033[0m"
	echo -e "\033[1m***CLEAR CPPCHECKER ERRORS TO CONTINUE***\033[0m"
	cat testapp_cppchecker_errors.txt
	exit 1
fi

echo "Static Analysis Run: Coverity"
echo "Running Coverity for qdma pmd"
cd `pwd`/../..
make config T=x86_64-native-linuxapp-gcc
chmod +x ../../../util/common/coverity/*
../../../util/common/coverity/run_coverity.sh -o ../../../util/common/coverity/output/pmd_output_$(date +"%Y%m%d_%H%M%S") "make " > .tmp_pmd_log
sed -n '/Defect occurrences found/p' .tmp_pmd_log | cut --complement -d ':' -f 1 | cut -d ' ' -f 2 > .tmp_cov_errors
cv_errs=$(cat .tmp_cov_errors)
if [ "${cv_errs}" != "${pmd_coverity_errors_orig}" ]; then
	echo "-------------------"
	echo -e "\033[1m***New Coverity errors are introduced in dpdk pmd code***\033[0m"
	echo "-------------------"
fi

echo "Running Coverity for qdma testapp"
cd ${testapp_dir}
export RTE_SDK=`pwd`/../..
export RTE_TARGET=build
chmod +x ../../../../../util/common/coverity/*
../../../../../util/common/coverity/run_coverity.sh -o ../../../../../util/common/coverity/output/testapp_output_$(date +"%Y%m%d_%H%M%S") "make " > .tmp_testapp_log
sed -n '/Defect occurrences found/p' .tmp_testapp_log | cut --complement -d ':' -f 1 | cut -d ' ' -f 2 > .tmp_cov_errors
cv_errs=$(cat .tmp_cov_errors)
if [ "${cv_errs}" != "${testapp_coverity_errors_orig}" ]; then
	echo "-------------------"
	echo -e "\033[1m***New Coverity errors are introduced in dpdk testapp code***\033[0m"
	echo "-------------------"
fi
