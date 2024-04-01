#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 
#include <linux/blkdev.h>

MODULE_LICENSE("GPL");

int driver_major = 0;

struct file_operations driver_fops = {
    .owner = THIS_MODULE,
};


static int driverInit(void){
    int rc;

    printk(KERN_ALERT "Inserting Driver %d\n", driver_major);
    rc = register_blkdev(driver_major, "iocltDriver");

    if(rc < 0)
        return rc;
    if(driver_major == 0)
        driver_major = rc;

    return 0;
}

static void driverExit(void){
    printk(KERN_ALERT "Removing Driver %d\n", driver_major);
    unregister_blkdev(driver_major, "iocltDriver");
}

module_init(driverInit);
module_exit(driverExit);