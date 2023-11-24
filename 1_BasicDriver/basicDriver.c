#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 

MODULE_LICENSE("GPL");

static int hellostart(void){
    printk(KERN_ALERT"Inserting yoktoDriver\n");
}

static void helloexit(void){
    printk(KERN_ALERT "Removing yoktoDriver %d\n", module_major);
}


module_init(hellostart);
module_exit(helloexit);