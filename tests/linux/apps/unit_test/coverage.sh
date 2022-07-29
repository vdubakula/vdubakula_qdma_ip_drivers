#!/bin/bash -e

if [[ "${BASH_SOURCE[0]}" != "${0}" ]]
then
    echo "ERROR: Sourcing script is not supported - exiting"
else

    # Where the tools needed are to be found
    LCOV_DIR=/group/cdc_ir/projects/xilinx-2000/xmc_firmware-0175/shared/tools/lcov-1.13
    LCOV_CONFIG=$LCOV_DIR/etc/lcovrc
    export PATH=$LCOV_DIR/bin:$PATH

    Usage()
    {
        echo "Usage: `basename $0` [-h] -b <build_dir> -s <source_dir> [-e <executable_dir>] -o <output_dir>"
        echo
        echo "-h    Display usage instructions and exit"
        echo "-b    Build directory e.g. build/host/cmc_fw/src"
        echo "-s    Source code directory e.g. cmc_fw/src"
        echo "-e    Executable directory e.g. build/host/cmc_test/unit_test"
        echo "-o    Output directory e.g. report"
        echo
        echo "NOTE - switches -b, -s and -o are required!"
        echo "NOTE - if switch -e is specified, executables detected under that directory will be run"
        exit 1;
    }

    BUILD_DIR=
    SOURCE_DIR=
    EXE_DIR=
    OUTPUT_DIR=

    while getopts ":b:s:e:o:h" opt
    do
        case "${opt}" in
            h)
                Usage >&2
                ;;
            b)
                BUILD_DIR=$OPTARG
                ;;
            s)
                SOURCE_DIR=$OPTARG
                ;;
            e)
                EXE_DIR=$OPTARG
                ;;
            o)
                OUTPUT_DIR=$OPTARG
                ;;
            \?)
                echo "Invalid option: -$OPTARG" >&2
                exit 1
                ;;
            :)
                echo "Option -$OPTARG requires an argument." >&2
                exit 1
                ;;
            *)
                Usage >&2
                exit 1
                ;;
        esac
    done

    # Validate options
    if [[ -z $BUILD_DIR ]]
    then
        echo "The -b option is required"
        exit 1
    fi

    if [[ -z $SOURCE_DIR ]]
    then
        echo "The -s option is required"
        exit 1
    fi

    if [[ -z $OUTPUT_DIR ]]
    then
        echo "The -o option is required"
        exit 1
    fi

    # Get list of testcase executables to run (if any)
    EXE_LIST=
    if [[ ! -z $EXE_DIR ]]
    then
        EXE_LIST=$(find $EXE_DIR -executable -type f)

        if [[ -z $EXE_LIST ]]
        then
            echo "ERROR: No executables found under specified path: $EXE_DIR"
            exit 1
        fi
    fi

    # Create directory for generated output (if necessary)
    if [ ! -d "$DIRECTORY" ]
    then
        mkdir -p $OUTPUT_DIR
    fi

    # Gather baseline coverage data
    lcov --config-file $LCOV_CONFIG -c -i -d "$BUILD_DIR" -b "$SRC_DIR" -o "$OUTPUT_DIR/baseline.info"

    # Run tests (if applicable) - ignore test failures
    set +e
    for TESTCASE in $EXE_LIST
    do
        ${TESTCASE}
    done
    set -e

    # Gather actual coverage data
    lcov --config-file $LCOV_CONFIG -c -d "$BUILD_DIR" -b "$SRC_DIR" -o "$OUTPUT_DIR/executed.info"

    # Consolidate actual coverage data with the baseline data
    lcov --config-file $LCOV_CONFIG -a "$OUTPUT_DIR/baseline.info" -a "$OUTPUT_DIR/executed.info" -o "$OUTPUT_DIR/result.info"

    # Generate HTML report
    genhtml --config-file $LCOV_CONFIG $OUTPUT_DIR/result.info -o $OUTPUT_DIR
fi
