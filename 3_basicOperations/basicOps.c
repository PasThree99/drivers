#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 

MODULE_LICENSE("GPL");

// #####################
// GLOBALS
// #####################

#define RC_SUCCESS 0 
#define RC_FAIL 1 

int module_major = 0;

static int yoktoOpen(struct inode *inode, struct file *filp) {
    printk(KERN_ALERT "Device opened successfully\n");
    return RC_SUCCESS;
}

static int yoktoClose(struct inode *inode, struct file *filp){
       printk(KERN_ALERT "Device closed\n");
       return RC_SUCCESS;
}


struct file_operations yokto_fops = {
    .owner = THIS_MODULE,
    .open = yoktoOpen,
    .release = yoktoClose,
};


static int hellostart(void){
    
    int rc;

    printk(KERN_ALERT"Inserting yoktoDriver\n");

    // Dinamyc registration
    rc = register_chrdev(module_major, "yokto", &yokto_fops);

    // ERROR
    if(rc < 0)
        return rc;
    if(module_major == 0)
        module_major = rc;
    
    return RC_SUCCESS;
}

static void helloexit(void){
    printk(KERN_ALERT "Removing yoktoDriver %d\n", module_major);
    unregister_chrdev(module_major, "yokto");
}




module_init(hellostart);
module_exit(helloexit);
