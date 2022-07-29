add_library(xlnx INTERFACE)
IF(DPDK)
target_include_directories(xlnx INTERFACE xlnx_common xlnx_dpdk)
ENDIF(DPDK)

IF(LINUX)
target_include_directories(xlnx INTERFACE xlnx_common xlnx_linux)
ENDIF(LINUX)

