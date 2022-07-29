cmake_minimum_required(VERSION 3.9)
add_subdirectory(third_party/googletest-v1.8.0)#gtest library path.
add_subdirectory(qdma_access_test)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/qdma_access_test/qdma_access/*.c)
file(REMOVE ${SOURCE_FILES})
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/qdma_access_test/qdma_access/*.h)
file(REMOVE ${HEADER_FILES})
make_directory(${CMAKE_CURRENT_SOURCE_DIR}/qdma_access_test/qdma_access)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../sw_host/qdma_access
     DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/qdma_access_test/)
