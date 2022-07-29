#!/bin/bash

target=all
if [ ! -z $1 ]; then
	target=$1
fi

checkpach_mandate=1
exit_on_cp_errs=1
coverity_mandate=0
coverity_errors_orig="177"
sphinx_doc_mandate=0
exit_on_doc_errs=0
cppchecker_mandate=0
sparse_mandate=0
qdma_access_test=0
ktf_test=0

driver_include_path=driver/include
apps_path=apps
common_src=../qdma_access
checkpatch=../../util/common/checkpatch/checkpatch.pl
sphinx_doc_path=docs/git_doc
copyright_script=../../util/common/scripts/copyright_header.py
libqdma_path=driver/libqdma


if [ ! -e ${checkpatch} ]; then
	echo "***WARNING: Checkpatch file does not exist"
	checkpach_mandate=0
fi


function print_errs() {
	while read -r line; do
		echo $line
 	done <<< "$1"
}

function run_checkpatch() {
	chmod +x ${checkpatch}
	make clean
	echo "Running checkpatch"
	${checkpatch} --no-tree -f --show-types --ignore NOT_UNIFIED_DIFF,OOM_MESSAGE,LINUX_VERSION_CODE,SYMBOLIC_PERMS,UNNECESSARY_CASTS,ALLOC_WITH_MULTIPLY,DEPRECATED_VARIABLE,CONST_STRUCT,NON_OCTAL_PERMISSIONS ../qdma_access/*/* ../qdma_access/*.c ../qdma_access/*.h ${libqdma_path}/* driver/src/* > .tmp_cp_log
	cp_errs=$(cat .tmp_cp_log | grep "ERROR\|WARNING\|FILE")
	rm -f .tmp_cp_log
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

function run_coverity() {
	echo "Running coverity"
	../../util/common/coverity/run_coverity.sh -o ../../util/common/coverity/output/output_$(date +"%Y%m%d_%H%M%S") "make $@"
	sed -n '/Defect occurrences found/p' .tmp_cv_log | cut --complement -d ':' -f 1 | cut -d ' ' -f 2 > .tmp_cov_errors
	cv_errs=$(cat .tmp_cov_errors)
	if [ "${cv_errs}" != "${coverity_errors_orig}" ]; then
		echo "-------------------"
		echo -e "\033[1m***New Coverity errors are introduced in the code***\033[0m"
		echo "-------------------"
	fi
}

function generate_doc() {
	echo "Generating documentation"
	cd ${sphinx_doc_path}
	make html >> .tmp_doc_log
	doc_errs=$(cat .tmp_doc_log | grep "ERROR\|WARNING\|FILE")
	rm -f .tmp_doc_log
	if [ "${doc_errs}" != "" ]; then
		echo "----------------------------"
		echo "Sphinx Documentation Errors:"
		echo "----------------------------"
		print_errs "${doc_errs}"
		if [ ${exit_on_doc_errs} -ne 0 ]; then
			echo ""
			echo -e "\033[1m***CLEAR SPHINX DOCUMENATION ERRORS TO CONTINUE***\033[0m"
			echo ""
			exit 1
		fi
	fi
	cd -
}

function clean_doc() {
	echo "Cleaning documentation"
	cd ${sphinx_doc_path}
	make clean
	cd -
}

function run_cppchecker() {
	echo "Running cppchecker"
	rm cppchecker_errors.txt cppchecker_err.txt cppchecker_err_orig.txt
	if [ ! -f "../../util/linux/cppchecker/cppchecker_avoided_errors.txt" ]; then
		echo -e "\033[1m***ERROR KNOWN ERROR FILE NOT PRESENT***\033[0m"
		echo ""
		exit 1
	fi
	cppcheck --suppress=variableScope --enable=all -DBIT -DBITS_PER_BYTE -DBITS_PER_LONG -DBITS_PER_LONG_LONG -DCHAR_BIT -DGENMASK -DGENMASK_ULL -DGENL_ID_GENERATE -DARRAY_SIZE --inconclusive --force . 2> cppchecker_err.txt
	cp cppchecker_err.txt cppchecker_err_orig.txt
	sed  -i 's/:[0-9]*/:/' cppchecker_err.txt
	diff -uh ../../util/linux/cppchecker/cppchecker_avoided_errors.txt cppchecker_err.txt | egrep '^\\+' | egrep -v \'^\+\+\' > cppchecker_errors.txt
	read cpperr <<< $( wc -l cppchecker_errors.txt | awk '{ print $1 }' )
	if [ -z $cpperr > 0 ]; then
		echo -e "\033[1m*** $cpperr New errors found by cppchecker***\033[0m"
		echo -e "\033[1m***CLEAR CPPCHECKER ERRORS TO CONTINUE***\033[0m"
		cat cppchecker_errors.txt
		exit 1
	fi
}

function qdma_test() {
	pwd=`pwd`
	echo "Running qdma_test"
	cd ../../sw_test/linux/apps/unit_test/
	tar -zxf third_party/release-1.8.0.tar.gz
	cd googletest-release-1.8.0
	mkdir build
	cd build
	cmake -DBUILD_SHARED_LIBS=ON ../
	make
	mkdir ../../googletest-release-1.8.0/lib
	cp ./googlemock/*.so ../../googletest-release-1.8.0/lib
	pwd
	cd ../../
	pwd
	mkdir build;cd build
	cmake ..
	sed -i 's/static struct eqdma_hw_err_info eqdma/struct eqdma_hw_err_info eqdma/' ../qdma_access_test/qdma_access/eqdma_soft_access/eqdma_soft_access.c
	sed -i 's/static struct xreg_info qdma/struct xreg_info qdma/' ../qdma_access_test/qdma_access/qdma_cpm4_access/qdma_cpm4_access.c
	sed -i 's/static struct xreg_info eqdma/struct xreg_info eqdma/' ../qdma_access_test/qdma_access/qdma_cpm5_access/qdma_cpm5_access.c
	sed -i 's/static struct xreg_info eqdma/struct xreg_info eqdma/' ../qdma_access_test/qdma_access/eqdma_soft_access/eqdma_soft_access.c
	sed -i 's/static struct qdma_hw_err_info qdma/struct qdma_hw_err_info qdma/' ../qdma_access_test/qdma_access/qdma_soft_access/qdma_soft_access.c
	make
	if [ $? != 0 ]; then
		echo "Compilation failed"
		cd $pwd
		return
	fi
	./qdma_access_test/qdma_access_test_app
	cd $pwd
	pwd
	sleep 20


}

function ktf_test() {
	echo "Running KTF test"
    if [ -d "../../sw_test/linux/apps/ktf/build" ]; then
        rm -rf ../../sw_test/linux/apps/ktf/build
    fi
	pwd=`pwd`
	cd ../../sw_test/linux/apps/ktf/
	autoreconf
	cd ..
	mkdir -p build/ktf
	cd build/ktf/
	ktf_dir=`readlink -f ../../ktf/configure`
	echo $ktf_dir
	eval "$ktf_dir KVER=$(uname -r)"
	chmod +x ../../ktf/scripts/*
	cp ../../../../../sw_host/qdma_access/ qdma/ -r
	cp ../../../../../sw_host/linux/driver/libqdma/ qdma/ -r
	make
	echo "Inserting KTF modules"
	insmod kernel/ktf.ko
	insmod qdma/qdma_test.ko
	echo "Executing KTF test"
	./user/ktfrun
	cd $pwd
	rmmod qdma_test.ko
	rmmod ktf.ko
}

function run_sparse() {
	echo "Running sparse"
	rm sparse_pf_err.txt sparse_vf_err.txt sparse_err.txt sparse_pf_err_orig.txt sparse_vf_err_orig.txt
	if [ ! -f "../../util/linux/sparse/sparse_avoided_errors.txt" ]; then
		echo -e "\033[1m***ERROR KNOWN ERROR FILE NOT PRESENT***\033[0m"
		echo ""
		exit 1
	fi
	make apps
	make driver C=1 MODULE=mod_pf $@ 2>sparse_pf_err.txt
	make driver C=1 MODULE=mod_vf $@ 2>sparse_vf_err.txt
	cp sparse_pf_err.txt sparse_pf_err_orig.txt
	cp sparse_vf_err.txt sparse_vf_err_orig.txt
	sed  -i 's/:[0-9]*/:/' sparse_pf_err.txt
	sed  -i 's/::[0-9]*/:/' sparse_pf_err.txt
	sed  -i 's/.*HEAD//' sparse_pf_err.txt
	diff -u ../../util/linux/sparse/sparse_avoided_errors.txt sparse_pf_err.txt | grep '^\+' |  sed -E 's/^\+//' > sparse_errors.txt
	sed  -i 's/:[0-9]*/:/' sparse_vf_err.txt
	sed  -i 's/::[0-9]*/:/' sparse_vf_err.txt
	sed  -i 's/.*HEAD//' sparse_vf_err.txt
	diff -u ../../util/linux/sparse/sparse_avoided_errors.txt sparse_vf_err.txt | grep '^\+' |  sed -E 's/^\+//' >> sparse_errors.txt
	read sparse_errs <<< $( wc -l sparse_errors.txt | awk '{ print $1 }' )
	if [ $sparse_errs -gt 2 ]; then
		echo -e "\033[1m*** $sparse_errs New errors found by sparse***\033[0m"
		cat sparse_errors.txt
		#cd -
		exit 1
	fi
	exit 0
}

if [ $target == clean ]; then
	if [ -d ${libqdma_path}/qdma_access ] ; then
		rm -rf ${libqdma_path}/qdma_access
		rm -rf ${apps_path}/include/
	fi
	clean_doc
else
	#running checkpatch script
	if [ ! -d $common_src ]; then
		echo "common source direcotry does not exist"
		exit 1
	fi
	rm -rf ${libqdma_path}/qdma_access
	if [ ${checkpach_mandate} -ne 0 ]; then
		run_checkpatch
	fi
	cp -rf ${common_src} ${libqdma_path}/
	chmod -R 0777 ${libqdma_path}/qdma_access
	chmod -R +w ${libqdma_path}/qdma_access/*
	python ${copyright_script} -d ${libqdma_path}/qdma_access -c license.txt -a -f > /dev/null
	python ${copyright_script} -d ${libqdma_path}/qdma_access/qdma_soft_access -c license.txt -a -f > /dev/null
	python ${copyright_script} -d ${libqdma_path}/qdma_access/qdma_cpm4_access -c license.txt -a -f > /dev/null
	python ${copyright_script} -d ${libqdma_path}/qdma_access/eqdma_soft_access -c license.txt -a -f > /dev/null
	python ${copyright_script} -d ${libqdma_path}/qdma_access/eqdma_cpm5_access -c license.txt -a -f > /dev/null
	cp -rf ${driver_include_path} ${apps_path}/
	chmod -R 0777 ${apps_path}/include
	chmod -R +w ${apps_path}/include/*
	python ${copyright_script} -d ${apps_path}/include/ -c bsd_license.txt -f > /dev/null
fi
if [ $target == all ]; then

	if [ ${qdma_access_test} -ne 0 ]; then
		qdma_test
        exit
	fi
	if [ ${ktf_test} -ne 0 ]; then
		ktf_test
        exit
	fi
	if [ ${coverity_mandate} -ne 0 ]; then
		run_coverity
	fi
	if [ ${cppchecker_mandate} -ne 0 ]; then
		run_cppchecker
	fi
	if [ ${sphinx_doc_mandate} -ne 0 ]; then
		generate_doc
	fi
	if [ ${sparse_mandate} -ne 0 ]; then
		run_sparse
	fi
fi
make $@
