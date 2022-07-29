/*
 * Copyright (c) 2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#define PAGE_SIZE ((size_t)getpagesize())
#define PAGE_MASK ((uint64_t)(long)~(PAGE_SIZE - 1))
#define BYTES_PER_WORD (sizeof(uint32_t))

// Byte Reverse
void c_byte_rev(char *c) {

    char* temp = new char [BYTES_PER_WORD];

    temp[0] = c[0];
    temp[1] = c[1];
    temp[2] = c[2];
    temp[3] = c[3];

    c[0] = temp[3];
    c[1] = temp[2];
    c[2] = temp[1];
    c[3] = temp[0];

    return;
}

int main(int argc, char **argv)
{
    if ((argc != 2) && (argc != 3)) {
        fprintf(stderr, "usage: %s DEVICE_LOCATION [Write_file if in write mode]\n", argv[0]);
        return 1;
    }

    // Device location -- bus:device.function number (eg. 0000:03:00.0)
    std::string devlocation = std::string ( "/sys/bus/pci/devices/" ) + argv[1] + std::string ( "/config" );

    if (argc == 2) {
        // Read the Config Space 
        std::string readcommand = std::string ( "hexdump " ) + devlocation;
        system ( readcommand.c_str() );
    } else {

	std::ifstream bitstreamInput (argv[2], std::ifstream::binary);
	if(!bitstreamInput) {
	    fprintf(stderr, "The file you provided can't be read!");
	    return 1;
	}

	// Get some storage spaces
        std::string writecommand = "";
        char* writedata = new char [BYTES_PER_WORD];
	int bitstreamLength = 0;
	int bitstreamWords = 0;

	// get length of file:
	bitstreamInput.seekg (0, bitstreamInput.end);
	bitstreamLength = bitstreamInput.tellg();
	bitstreamWords = ((bitstreamLength / BYTES_PER_WORD) + ((bitstreamLength % BYTES_PER_WORD) ? 1 : 0));
	bitstreamInput.seekg (0, bitstreamInput.beg);

	std::cout << "We have this many words to write: " << bitstreamWords << std::endl;

	// Open Config Space File
	std::fstream conffile( devlocation.c_str(), std::fstream::out | std::fstream::in | std::fstream::binary );

	while (bitstreamWords > 0) {

	    bitstreamInput.read(writedata,BYTES_PER_WORD);

	    c_byte_rev(writedata);

            conffile.seekp (856, std::ofstream::beg); // This is the location of the MCAP Data Register
	    conffile.write (writedata, sizeof(writedata));

	    bitstreamWords--;
        }

	// Close Config Space File
	conffile.close();

    }

    return 0;
}
