###############################################################################

               Xilinx QDMA Windows Driver Documentation Generation

###############################################################################


1. Extract the git_doc.zip which contains all the tools and templates to create the documentation
	unzip git_doc.zip
2. Copy source folder to the extracted git_doc folder
	cp -fr source/ git_doc/.
3. cd to git_doc folder
	cd git_doc
4. Source the environment file
	source env.csh
5. Run 'make' to generate the html files
	make
6. Open qdma_win\index.html to view QDMA Windows documentation
