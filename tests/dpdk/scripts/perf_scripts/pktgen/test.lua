package.path = package.path ..";?.lua;test/?.lua;app/?.lua;"
require "Pktgen"

pktgen.screen("off");
printf("\nHello World!!!!\n");
local pktgenaddr = os.getenv("PKT_GEN_ADDR");
local h2c_enaled = os.getenv("RUN_H2C");
local usrbaraddr = tonumber(pktgenaddr, 16);
local data = 64;
printf("\nuser bar addr %x\n", usrbaraddr);
system(strfmt("./devmem 0x%x w %d", usrbaraddr+0x90, data));
system(strfmt("./devmem 0x%x w 0x120000", usrbaraddr+8));
init_data = {64, 128, 192, 256, 384, 512, 768, 1024, 1280, 1518, 2048, 2560, 3072, 3584, 4096};
while data<4097 do
	printf("\n \n *********C2H Packet size %d \n", data);
	system(strfmt("./devmem 0x%x w %d", usrbaraddr+0x90, data));
	pktgen.delay(10000);
	prints("portRates", pktgen.portStats("all", "rate"));
	pktgen.delay(1000);
	data = data + 64;
end
system(strfmt("./devmem 0x%x w 0x240000", usrbaraddr+8));
data = 64;
pktgen.delay(1000);
if h2c_enaled == "1" then
	while data<4097 do
		pktgen.set("all", "size", data);
		pktgen.start("all");
		pktgen.delay(10000);
		printf(" \n \n *****H2C Packet size %d \n", data);
		prints("portRates", pktgen.portStats("all", "rate"));
		pktgen.delay(1000);
		pktgen.stop("all");
		pktgen.delay(1000);
		data = data + 64;
	end
end
pktgen.quit();

