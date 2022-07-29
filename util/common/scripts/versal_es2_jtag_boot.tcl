proc programload_versal {} {
        connect
 
        #tar -set -filter {name =~ "Versal xcv350*"}
        #tar -set -filter {name =~ "Versal xcvc190*"}
		ta 1
 
        # Switch to JTAG mode
        mwr 0xf1260200 0x0100
        mrd 0xf1260200
 
        # SYSMON_REF_CTRL is switched to NPI by user PDI so ensure its
        #  switched back
        mwr -force 0xF1260138 0

        # Perform reset
        tar -set -filter {name =~ "DPC"}
        mwr 0xF1110004 0x0
        after 10
	    mwr -force 0xF126031C 0xE
		after 10
        #tar -set -filter {name =~ "Versal xcv350*"}
        #tar -set -filter {name =~ "Versal xcvc190*"}
		ta 1
 
       configparams default-config-timeout 30000

 }
programload_versal
