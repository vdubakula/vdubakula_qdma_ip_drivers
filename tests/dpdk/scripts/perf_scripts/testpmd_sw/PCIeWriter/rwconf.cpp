/*
 * Copyright (c) 2012-2022 Xilinx, Inc. All rights reserved.
 * Copyright (c) 2022-2023, Advanced Micro Devices, Inc. All rights reserved.
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

// Convert Binary to Hex + byte reverse it (convert endian-ness) + space it out every 16-bit
std::string ToHex_rev(const std::string& s) {
    std::ostringstream ret;
    std::string::size_type i = 0;

    for (i = s.length(); i > 2; i--) {
        int z = s[i-1]&0xff;
        ret << std::hex << std::setfill('0') << std::setw(2) << z;
    }

    ret << " ";

    for (i; i > 0; i--) {
        int z = s[i-1]&0xff;
        ret << std::hex << std::setfill('0') << std::setw(2) << z;
    }

    return ret.str();
}

int main(int argc, char **argv)
{
    if ((argc != 2) && (argc != 3)) {
        fprintf(stderr, "usage: %s DEVICE_LOCATION [Write_file if in write mode]\n", argv[0]);
        return 1;
    }

    // Commands currently not being used
        // Copy Config Space hex file to a local folder
        //std::string tempcommand = readcommand + std::string ( " | xxd -r >tempconfig" );
        //system ( tempcommand.c_str() );

    // Device location -- bus:device.function number (eg. 0000:03:00.0)
    std::string devlocation = std::string ( "/sys/bus/pci/devices/" ) + argv[1] + std::string ( "/config" );

    if (argc == 2) {
        // Read the Config Space
        std::string readcommand = std::string ( "hexdump " ) + devlocation;
        system ( readcommand.c_str() );
    } else {
        /** Substitute the data with the given input and write it back to the Config Space. The input format has to be:
            argument 1 = config space byte offset (in hex)
            argument 2 = Data to write (needs to be byte swapped! -- swap endian-ness) put space after 16 bits (eg ffff ffff)
        **/
	std::ifstream bitstreamInput (argv[2], std::ifstream::binary);
	if(!bitstreamInput) {
	    fprintf(stderr, "The file you provided can't be read!");
	    return 1;
	}

	// Get some storage spaces
        std::string writecommand = "";
        char* writedata = new char [BYTES_PER_WORD];
	std::string writeaddr = "0358"; // This is the location of the MCAP Data Register
	int bitstreamLength = 0;
	int bitstreamWords = 0;

	// get length of file:
	bitstreamInput.seekg (0, bitstreamInput.end);
	bitstreamLength = bitstreamInput.tellg();
	bitstreamWords = ((bitstreamLength / BYTES_PER_WORD) + ((bitstreamLength % BYTES_PER_WORD) ? 1 : 0));
	bitstreamInput.seekg (0, bitstreamInput.beg);

	std::cout << "We have this many words to write: " << bitstreamWords << std::endl;

	while (bitstreamWords > 0) {
	    bitstreamInput.read(writedata,BYTES_PER_WORD);

        writecommand = std::string ( "echo " ) + writeaddr + std::string ( " " )
                       + ToHex_rev(std::string(writedata,BYTES_PER_WORD))
                       + std::string ( " | xxd -r >" ) + devlocation;
        system ( writecommand.c_str() );

//	std::cout << ToHex_rev(std::string(writedata,BYTES_PER_WORD)) << std::endl;

	bitstreamWords--;
        }
    }

    return 0;
}
