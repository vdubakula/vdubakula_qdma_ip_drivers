#!/bin/bash

cov_path=/tools/batonroot/coverity/2019.09/bin
cov_cfg=cov-config
out_path=.
build_intermediate_dir=cov-intr
make_args=
compiler=gcc
#extra_analyze_opts="--allow-unmerged-emits --aggressiveness-level high --enable-parse-warnings --enable-default --enable-exceptions --enable-fnptr"
extra_analyze_opts="--aggressiveness-level high --enable-parse-warnings --enable-default --enable-exceptions --enable-fnptr -im exclude"
cov_build_extra_opts=

function usage() {
	echo "Arguments for this script are:"
	echo ""
	echo "-h|--help         usage guidelines"
	echo ""
	echo "--cov_path        Path to coverity binary"
	echo ""
	echo "--compiler        compiler being used for the build"
	echo ""
	echo "--cb_opts         extra cov-build opts"
	echo ""
	echo "-o|--out          directory to which coverity build/analyze and formatted output is posted"
	echo ""
	echo "Note: any other parameter is considred as source code build command. So no invalid arguments"
}

while [[ $# -gt 0  ]]
do
	case $1 in
		--cov_path)
			shift
			cov_path="$1"
			;;
		--compiler)
			shift
			compiler="$1"
			;;
		--cb_opts)
			shift
			cov_build_extra_opts="$1"
			;;
		-o|--out)
			shift
			out_path="$1"
			;;
		-h|--help)
			usage
			exit
			;;
		*)
			make_args="${make_args} $1"
			;;
	esac
	shift
done

if [ "${cov_build_extra_opts}" != "" ]; then
	echo "cov-build running with ${cov_build_extra_opts} extra options"
fi

function run_coverity() {
	echo "Running coverity"
	if [ -d ${out_path} ]; then
		rm -rf ${out_path}/*
	fi
	export PATH=${cov_path}:$PATH
	cov-configure --template --config ${out_path}/${cov_cfg}/coverity_config.xml --compiler ${compiler} 
	cov-build --config ${out_path}/${cov_cfg}/coverity_config.xml ${cov_build_extra_opts} --dir ${out_path}/${build_intermediate_dir} $@
	if [ $? -ne 0 ]; then
		echo "cov-build failed"
		exit 1
	fi
	cov-analyze --all --allow-unmerged-emits --aggressiveness-level high --enable-parse-warnings -enable-default --enable-exceptions --enable-fnptr --config ${out_path}/${cov_cfg}/coverity_config.xml --dir ${out_path}/${build_intermediate_dir}
	if [ $? -ne 0 ]; then
		echo "cov-analyze failed"
		exit 1
	fi
	cov-format-errors --config ${out_path}/${cov_cfg}/coverity_config.xml --html-output ${out_path}/formatted-output --dir ${out_path}/${build_intermediate_dir}
}

run_coverity ${make_args}
