# Try to find dpdk v17.11
#
# Once done, this will define
#
# DPDK_FOUND
# DPDK_INCLUDE_DIR
# DPDK_LIBRARIES

find_path(DPDK_INCLUDE_DIR rte_config.h
  PATH_SUFFIXES dpdk
  HINTS $ENV{RTE_SDK}/$ENV{RTE_TARGET}/include)

set(components
  acl bitratestats bus_pci bus_vdev cfgfile cmdline
  cryptodev distributor eal efd ethdev eventdev flow_classify gro gso hash
  ip_frag jobstats kni kvargs latencystats lpm mbuf member stack mempool 
  mempool_ring mempool_stack meter metrics net pci pdump pipeline
  net_af_packet net_kni  net_null 
  net_qdma net_ring event_skeleton event_sw
  net_tap  net_vhost net_virtio port power reorder
  ring sched security table timer vhost)

foreach(c ${components})
  find_library(DPDK_rte_${c}_LIBRARY rte_${c}
    HINTS $ENV{RTE_SDK}/$ENV{RTE_TARGET}/lib)
#    message("library is ${DPDK_rte_${c}_LIBRARY}")
endforeach()

foreach(c ${components})
  list(APPEND check_LIBRARIES "${DPDK_rte_${c}_LIBRARY}")
endforeach()

mark_as_advanced(DPDK_INCLUDE_DIR ${check_LIBRARIES})


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(dpdk DEFAULT_MSG
  DPDK_INCLUDE_DIR
  check_LIBRARIES)

if(DPDK_FOUND)
    set(DPDK_LIBRARIES
    -Wl,--whole-archive ${check_LIBRARIES} -lpthread -lgcov -lnuma -ldl -Wl,--no-whole-archive)
endif(DPDK_FOUND)
