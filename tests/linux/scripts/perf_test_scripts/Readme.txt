1. make sure all required config files are in configs folder
2. make sure the folder structure is as below
    top
	  |
	  |- sw_host
	  |        |
	  | 	   |- mdma
	  | 	         |
	  | 			 |- linux
	  |- sw_test
	           |
			   | - scripts
			             |
						 |- perf_scripts
						 
3. build qdma driver in 'linux' folder
4. run ./run_tests <bus_num> <out_folder_name>	  