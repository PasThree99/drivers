#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 

int module_major = 0;
char *module_name = "simpleRead";

struct file_operations module_fops = {
    .owner = THIS_MODULE,
    .read = moduleRead,
    .open = moduleOpen,
    .release = moduleClose,
};

static int moduleOpen(struct inode *inode, struct file *filp){
    printk(KERN_INFO "Open success");
    return 0;
}

static int moduleClose(struct inode *inode, struct file *filp){
    printk(KERN_INFO "Close: success");
    return 0;
}

static ssize_t moduleRead(struct file *filp, char __user *buf, size_t count, loff_t *f_pos){
    char msg = "This is a simple read";
    ssize_t bytes_to_read = strlen(msg);
    
    if (copy_to_user(buf, msg, bytes_to_copy) != 0) {
        return -EFAULT; 
    }

    return bytes_to_read;
}

static int moduleInit(void){
    int rc;

    rc = register_chrdev(module_major, module_name, &module_fops);

    if (rc < 0 )
        return rc;

    if (module_major == 0)
        module_major = rc;
    
    return 0;
}

static void moduleExit(void){
    unregister_chrdev(module_major, module_name);
}


module_init(moduleInit);
module_exit(moduleExit);