package.path = package.path ..";?.lua;test/?.lua;app/?.lua;"
require "Pktgen"

pktgen.screen("off");
printf("\nHello World!!!!\n");
local pktgenaddr = os.getenv("PKT_GEN_ADDR");
local h2c_enaled = os.getenv("RUN_H2C");
local usrbaraddr = tonumber(pktgenaddr, 16);
--local usrbaraddr = 0xfe004000;
local data = 63;
local data_set = 63;
printf("\nuser bar addr %x\n", usrbaraddr);
pktgen.delay(1000);
while data<4097 do
        while data_set == data do
                pktgen.delay(8000);
                system(strfmt("./devmem 0x%x > /tmp/memtemp", usrbaraddr+0x90))
                system("chmod -R 777 /tmp/memtemp")
                for line in io.lines("/tmp/memtemp") do
                        size = line:match(":%s0x(.+)")
                        if size then
                                size = tonumber(size, 16);
                                break;
                        end
                end
                data_set = size;
                pktgen.delay(1000);
        end
        printf("\n \n *********C2H Packet size %d \n", data_set);
        data = data_set;
        pktgen.delay(10000);
        prints("portRates", pktgen.portStats("all", "rate"));
        pktgen.delay(1000);
        if data == 4096 then
            break;
        end
end
pktgen.delay(1000);
system(strfmt("./devmem 0x%x w 0x240000", usrbaraddr+8));
data = 4096;
data_set = 4096;
--pktgen.delay(1000);
if h2c_enaled == "1" then
    while data<4097 do
        while data_set == data do
                pktgen.delay(4000);
                system(strfmt("./devmem 0x%x > /tmp/memtemp", usrbaraddr+0x90))
                system("chmod -R 777 /tmp/memtemp")
                for line in io.lines("/tmp/memtemp") do
                        size = line:match(":%s0x(.+)")
                        if size then
                                size = tonumber(size, 16);
                                break;
                        end
                end
                data_set = size;
                pktgen.delay(1000);
        end
		data = data_set;
        --pktgen.delay(10000);
        pktgen.set("all", "size", data);
        pktgen.start("all");
        pktgen.delay(5000);
        printf(" \n \n *****H2C Packet size %d \n", data);
        prints("portRates", pktgen.portStats("all", "rate"));
        pktgen.delay(30000);
        pktgen.stop("all");
        --pktgen.delay(1000);
        -- data = data + 64;
        if data == 4096 then
            break;
        end
    end
end
pktgen.quit();