Steps to install KTF :

	- cd <perforce_path>/sw_test/apps/qdma/linux/<ktf_dir>
	- Execute the following command: autoreconf
	- cd sw_test/apps/qdma/linux/
	- mkdir -p build/ktf
	- cd build/ktf
	- Execute the following command: : <perforce_path>/sw_test/apps/qdma/linux/<ktf_dir>/configure KVER=$(uname -r)
	- Copy the libqdma and qdma_access folders to <perforce_path>/sw_test/apps/qdma/linux/build/ktf/qdma directory.
	- Execute the following command: make


Steps to run KTF

	- insmod kernel/ktf.ko
	- insmod qdma/qdma_test.ko
	- user/ktfrun ( this will run all the unit tests for libqdma)
	
	
	