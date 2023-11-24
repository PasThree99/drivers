#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 

MODULE_LICENSE("GPL");

static int hellostart(void){
    printk(KERN_ALERT"Inserting driver\n");
    return 0;
}

static void helloexit(void){
    printk(KERN_ALERT "Removing driver\n");
}


module_init(hellostart);
module_exit(helloexit);