cmd_/home/parallels/Documents/driversRepo/drivers/8_BlockIoctl/Module.symvers := sed 's/\.ko$$/\.o/' /home/parallels/Documents/driversRepo/drivers/8_BlockIoctl/modules.order | scripts/mod/modpost -m -a  -o /home/parallels/Documents/driversRepo/drivers/8_BlockIoctl/Module.symvers -e -i Module.symvers   -T -
