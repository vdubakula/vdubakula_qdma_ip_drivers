Procedure to integrated qdma pmd into dpdk, and building it :
=============================================================
1. Get the dpdk-17.11.1 from open source.
    git clone http://dpdk.org/git/dpdk-stable
	git checkout v17.11.1 OR git checkout v17.11

2. cd dpdk;

3. git am 0001-net-qdma-Integrate-qdma-pmd-to-dpdk-17.11.1.patch
   Note : if you are not having git tree, then use legacy 'patch' command.

4.Now copy the /drivers/net/* and /examples from perforce to respective directories of dpdk.
   cp <perforce>/xdma/dpdk/drivers/net/qdma  <dpdk-open-source>/drivers/net
   cp <perforce>/xdma/dpdk/examples/* <dpdk-open-source>/examples/

5. To build the qdma pmd, go through /exmaples/qdma_testapp/REAME.txt

