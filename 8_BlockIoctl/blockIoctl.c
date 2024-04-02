#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 
#include <linux/blkdev.h>

MODULE_LICENSE("GPL");

int driver_major = 0;
int driver_minor = 1;

struct file_operations driver_fops = {
    .owner = THIS_MODULE,
};

static struct my_block_dev {
    struct gendisk *gd;
} dev;


static int driverInit(void){
    int rc;

    printk(KERN_ALERT "Inserting Driver %d\n", driver_major);
    rc = register_blkdev(driver_major, "iocltDriver");

    if(rc < 0)
        return rc;
    if(driver_major == 0)
        driver_major = rc;

    dev->gd = alloc_disk(driver_minor);
    add_disk(dev->gd);
    
    return 0;
}

static void driverExit(void){
    printk(KERN_ALERT "Removing Driver %d\n", driver_major);
    unregister_blkdev(driver_major, "iocltDriver");
}

module_init(driverInit);
module_exit(driverExit);