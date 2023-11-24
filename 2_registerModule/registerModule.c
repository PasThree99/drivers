#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 

MODULE_LICENSE("GPL");

int module_major = 0;


struct file_operations driver_fops = {
    .owner = THIS_MODULE,
};

static int hellostart(void){
    
    int rc;

    printk(KERN_ALERT"Inserting driver\n");

    /*
     * Dinamyc registration:
     * When register chardev is invoked with MAJOR = 0, the kenel
     * will dinamicly find a available number to register the module
     * with and return it. Note that any number less than 0 is en error
     */ 

    rc = register_chrdev(module_major, "registerDriver", &driver_fops);

    // ERROR
    if(rc < 0)
        return rc;
    if(module_major == 0)
        module_major = rc;
    
    return 0;
}

static void helloexit(void){
    printk(KERN_ALERT "Removing driver %d\n", module_major);
    unregister_chrdev(module_major, "registerDriver");
}


module_init(hellostart);
module_exit(helloexit);
