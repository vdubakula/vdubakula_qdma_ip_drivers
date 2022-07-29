###############################################################################

               Xilinx QDMA DPDK Driver Documentation Generation

###############################################################################

Notes:
=========
1. Update the Driver version number in source/conf.py
2. Make sure to review the source/*.rst files and update the content if required
3. Make sure, all the externel APIs listed in dpdk/drivers/net/qdma/rte_pmd_qdma.h are documented properly


1. Extract the git_doc.tar.gz which contains all the tools and templates to create the documentation
	tar -xvf git_doc.tar.gz
2. Copy source folder to the extracted git_doc folder
	cp -fr source/ git_doc/.
3. cd to git_doc folder
	cd git_doc
4. Source the environment file
	source env.csh
5. Run 'make' to generate the html files
	make
6. Open qdma_dpdk\index.html to view QDMA DPDK documentation

