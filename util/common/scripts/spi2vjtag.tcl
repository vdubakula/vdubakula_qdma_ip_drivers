connect        
tar -set -filter {name =~ "Versal*"}
mwr 0xf1260200 0x0100    
mrd 0xf1260200
mwr -force 0xF1260138 0 
tar -set -filter {name =~ "PMC"}
rst     
after 10
tar -set -filter {name =~ "Versal*"}
mrd -force 0xF1120000
configparams default-config-timeout 30000    

