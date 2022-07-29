#!/bin/bash

src_dir=$1
compile_flags=$2
#${PWD}/../../sw_host/mdma/linux

echo "Static Analysis Run"
export PATH=/tools/batonroot/coverity/8.0.0/cov-analysis-8.0.0/bin:$PATH
mkdir -p /group/cdc_hd/members/coverity/config
cov-configure --template --config /group/cdc_hd/members/coverity/config/coverity_config.xml --compiler gcc
cd ${src_dir}
cov-build --config /group/cdc_hd/members/coverity/config/coverity_config.xml --dir . make ${compile_falgs}
cov-analyze --all --allow-unmerged-emits --aggressiveness-level high --enable-parse-warnings -enable-default --enable-exceptions --enable-fnptr --config /group/cdc_hd/members/coverity/config/coverity_config.xml --dir .
cov-format-errors --config /group/cdc_hd/members/coverity/config/coverity_config.xml --html-output /group/cdc_hd/members/coverity/config/output_$(date +"%Y%m%d_%H%M%S") --dir .
echo "Running CheckPatch script"
/lib/modules/4.14.40/source/scripts/checkpatch.pl --no-tree -f libqdma/*
cd -
