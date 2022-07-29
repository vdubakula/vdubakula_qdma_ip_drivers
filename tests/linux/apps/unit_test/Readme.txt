Steps to compile gtest :

	- untar the release-1.8.0.tar.gz
	- cd to googletest-release-v1.8.0
	- Create build directory
	- cd build
	- cmake -DBUILD_SHARED_LIBS=ON ../
	- make
	- cp ./googlemock/*.so ../googletest-v1.8.0/lib
	- cp ./googlemock/include/* ../googletest-v1.8.0/include
	- cp ./gtest/include/* ../googletest-v1.8.0/include

Steps to build unit test :

	- Create build directory in unit_test folder
	- cmake ..
	- make
	- in case there are errors due to static variables in the qdma_access files , remove the static keyword
	- Run ./qdma_access_test/qdma_access_test_app