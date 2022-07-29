
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


# We need thread support
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)


add_subdirectory(xlnx)

IF(DPDK)

	list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

	find_package (dpdk REQUIRED)

	set (RTE_TARGET x86_64-native-linuxapp-gcc)

	INCLUDE_DIRECTORIES(${DPDK_INCLUDE_DIR} qdma/qdma_common qdma/qdma_dpdk util ../include)

	add_executable(qdma_test main.cpp
                         	qdma/qdma_dpdk/qdma_instance.cpp
                         	qdma/qdma_dpdk/qdma_device.cpp
                         	qdma/qdma_dpdk/qdma_queue.cpp
                         	test/mm_tests.cpp
                         	test/st_tests.cpp
                         	test/pcie_tests.cpp
                         	test/threaded_dma_tests.cpp
                         	)
#     message("library is ${DPDK_LIBRARIES}")
    target_link_libraries(qdma_test PRIVATE GTest::GTest xlnx ${DPDK_LIBRARIES})

	target_include_directories(qdma_test PRIVATE ./)

    target_compile_definitions(qdma_test PRIVATE DPDK)



ENDIF(DPDK)


IF(LINUX)

	INCLUDE_DIRECTORIES(util qdma/qdma_common qdma/qdma_linux ../include)

	add_executable(qdma_test main.cpp
                         	qdma/qdma_linux/qdma_instance.cpp
                         	qdma/qdma_linux/qdma_device.cpp
                         	qdma/qdma_linux/qdma_queue.cpp
                         	test/nl_tests.cpp
                         	test/pcie_tests.cpp
                         	test/mm_tests.cpp
                         	test/st_tests.cpp
                         	test/threaded_dma_tests.cpp
                         	test/aio_mm_tests.cpp
                         	test/aio_st_tests.cpp
                         	test/dmactl_tests.cpp
                         	test/debugfs_tests.cpp
                         	)

	target_compile_features(qdma_test PRIVATE cxx_std_11)

	target_link_libraries(qdma_test PRIVATE GTest::GTest xlnx nl-3 nl-genl-3 aio)

	target_include_directories(qdma_test PRIVATE /usr/include/libnl3 ./)

    	target_compile_definitions(qdma_test PRIVATE LINUX)
    
ENDIF(LINUX)

IF(TEST_VF_ALONE)
	    target_compile_definitions(qdma_test PRIVATE TEST_VF_ALONE)
ENDIF(TEST_VF_ALONE)


target_compile_features(qdma_test PRIVATE cxx_std_11)

install(TARGETS qdma_test
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)

enable_testing()
add_test( qdma_test qdma_test )
