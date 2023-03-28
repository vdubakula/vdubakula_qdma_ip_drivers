#!/bin/sh
usrbarpktsize=$(($1 + 0x90))
./PCIeWriter/rwmem $usrbarpktsize $2
sleep 1