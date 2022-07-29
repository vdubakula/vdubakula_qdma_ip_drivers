
enable_testing()
include(GoogleTest)

# Options for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
add_definitions(-DUNITTEST)
add_compile_options(--coverage -g)
include_directories(${GMOCK_INCLUDE_DIR} qdma_access qdma_access/eqdma_soft_access qdma_access/qdma_cpm4_access qdma_access/qdma_soft_access ./)
link_libraries(${GMOCK_LIB} pthread gcov)

add_executable(qdma_access_test_app main.cpp
				qdma_access_common_test.cpp
				eqdma_access_test.cpp
				qdma_platform.cpp
				qdma_access/qdma_access_common.c
				qdma_access/eqdma_soft_access/eqdma_soft_access.c
				qdma_access/eqdma_soft_access/eqdma_soft_reg_dump.c
				qdma_access/qdma_cpm4_access/qdma_cpm4_access.c
				qdma_access/qdma_cpm4_access/qdma_cpm4_reg_dump.c
				qdma_access/qdma_soft_access/qdma_soft_access.c)

add_test( qdma_access_test_app qdma_access_test_app )