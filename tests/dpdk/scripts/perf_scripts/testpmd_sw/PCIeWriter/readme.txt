To add to your notes, if you want to test your memory from a Linux host, you should be able to do the following:
Copy attached C file to your host
‘gcc rwmem.c’
Rename the generated a.out to rwmem and make sure it’s executable
Run ‘lspci’
‘cat /proc/iomem’ and find your PCIe peripheral as displayed from lspci. Mine is at 0000:01:00:0.
The above step would have displayed the address range for each BAR of your peripheral. For example mine is 0xfff4f000
‘./rwmem 0xfff4f000’ should read from BAR0
‘./rwmem 0xfff4f000 0x12345678’ should write to BAR0
