#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 

MODULE_LICENSE("GPL");

int driver_major = 0;

struct file_operations module_fops = {
    .owner = THIS_MODULE,
};


static int driverInit(void){
    int rc;

    printk(KERN_ALERT "Inserting Driver %d\n", module_major);
    rc = register_blkdev(module_major, "iocltDriver", &driver_fops);

    if(rc < 0)
        return rc;
    if(module_major == 0)
        module_major = rc;

    return 0;
}

static void driverExit(void){
    printk(KERN_ALERT "Removing Driver %d\n", module_major);
    unregister_blkdev(module_major, "iocltDriver");
}

module_init(driverInit);
module_exit(driverExit);