cmd_/home/parallels/Documents/driversRepo/drivers/1_BasicDriver/modules.order := {   echo /home/parallels/Documents/driversRepo/drivers/1_BasicDriver/basicDriver.ko; :; } | awk '!x[$$0]++' - > /home/parallels/Documents/driversRepo/drivers/1_BasicDriver/modules.order