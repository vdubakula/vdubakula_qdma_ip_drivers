cmake_minimum_required (VERSION 3.5)
project (qdma_test)

SET(CMAKE_CXX_COMPILER /usr/bin/g++)

OPTION(DPDK "Compile DPDK Specific code" OFF)
OPTION(LINUX "Compile Linux Specific code" OFF)

if(MSVC)
    add_compile_options(/W3 /WX)
else()
IF(LINUX)
    add_compile_options(-Wall -Wpedantic -g -O0)
ENDIF(LINUX)
IF(DPDK)
    add_compile_options(-Wall -Wextra -g -O0 -march=native -fpermissive)
ENDIF(DPDK)
endif()

add_subdirectory(src)
