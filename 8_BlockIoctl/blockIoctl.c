#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 
#include <linux/blkdev.h>

MODULE_LICENSE("GPL");

#define NR_SECTORS                    1024
#define KERNEL_SECTOR_SIZE            512
int driver_major                    = 0;
int driver_minor                    = 1;


// #####################
//   IOCTL COMMANDS
// #####################

#define HELLO 1 
#define BYE 2 



int driverOpen(struct block_device *bdev, fmode_t mode){
    printk("Opening!");
}

int driverClose(struct block_device *bdev, fmode_t mode){
    printk("Closing!");
}

int driverIoctl(struct block_device *bdev, fmode_t mode, unsigned cmd, 
                unsigned long arg){
    
    switch (cmd)
    {
    case HELLO:
        printk(KERN_INFO "HELLO");
        break;
    case BYE:
        printk(KERN_INFO "GOOD BYE");
        break;
    default:
        printk(KERN_ERR "Unknown Command");
        break;
    }

    return 0;
}



struct file_operations driver_fops = {
    .owner  = THIS_MODULE,
    .open   = driverOpen,
    .close  = driverClose,
    .ioctl  = driverIoctl
};

static struct my_block_dev {
    struct gendisk *gd;             /* The gendisk structure */
    spinlock_t lock;                /* For mutual exclusion */
    struct request_queue *queue;    /* The device request queue */
} dev;


static int driverInit(void){
    int rc;

    printk(KERN_ALERT "Inserting Driver %d\n", driver_major);
    
    // Dinamyc allocation
    rc = register_blkdev(driver_major, "iocltDriver");
    if(rc < 0)
        return rc;
    if(driver_major == 0)
        driver_major = rc;

    // Fill the gendisk struct
    dev->gd = alloc_disk(driver_minor);
    dev->gd->major = MY_BLOCK_MAJOR;
    dev->gd->first_minor = 0;
    dev->gd->fops = &driver_fops;
    dev->gd->queue = dev->queue;
    dev->gd->private_data = dev;
    snprintf (dev->gd->disk_name, 32, "iocltDriver");
    set_capacity(dev->gd, NR_SECTORS);
    
    add_disk(dev->gd);
    return 0;
}

static void driverExit(void){
    printk(KERN_ALERT "Removing Driver %d\n", driver_major);
    if (dev->gd) {
        del_gendisk(dev->gd);
    }
    unregister_blkdev(driver_major, "iocltDriver");
}

module_init(driverInit);
module_exit(driverExit);