#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 

MODULE_LICENSE("GPL");

#define RC_SUCCESS 0;
#define RC_FAIL 1;

int major = 0;

struct my_device_data {
    int id;
    unsigned long timestamp;
    char data[256];
};


static int driverOpen(struct inode *inode, struct file *filp){
    struct my_device_data *myData = kmalloc(sizeof(struct my_device_data), GFP_KERNEL);
        if (!myData) {
        printk(KERN_ALERT "Failed to allocate memory for device data\n");
        return -ENOMEM;
    }

    filp->private_data = myData;
    printk(KERN_INFO "Device opened successfully\n");

    return RC_SUCCESS;
}

static int driverClose(struct inode *inode, struct file *filp){
    struct my_device_data *myData = filp->private_data;
    
    kfree(myData);
    printk(KERN_INFO "Device closed\n");

    return RC_SUCCESS;
}

static ssize_t driverWrite(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos){
    struct my_device_data *myData = filp->private_data;

    if (*f_pos != 0) {
        return -EINVAL;
    }

    if (copy_from_user(myData->data, buf, min(count, sizeof(myData->data)))) {
        return -EFAULT;
    }

    *f_pos += count;

    printk(KERN_INFO "Data written: %s\n", myData->data);

    return count; 
}

static ssize_t driverRead(struct file *filp, char __user *buf, size_t count, loff_t *f_pos){
    struct my_device_data *myData = filp->private_data;

    size_t bytes_to_copy = min(count, sizeof(myData->data));

    if(!copy_to_user(buf, myData, min(count, bytes_to_copy))){
        printk(KERN_ERR "Failed to read!");
        return -EFAULT;
    }

    return bytes_to_copy;
}



struct file_operations persistent_fops = {
    .owner = THIS_MODULE,
    .open = driverOpen,
    .write = driverWrite,
    .read = driverRead,
    .release = driverClose,
};

static int driverInit (void){
    int rc;

    rc = register_chrdev(major, "persistent", &persistent_fops);

    if (rc < 0){
        printk(KERN_ERR "Could not register module.  rc = %d", rc);
        return rc;
    }

    if(major == 0){
        major = rc;
        printk(KERN_INFO "Module registered with major %d", major);
    }
    return RC_SUCCESS;

}

static void driverExit (void){
    printk(KERN_INFO "Unregistering module with major %d", major);
    unregister_chrdev(major, "persistent");
}

module_init(driverInit);
module_exit(driverExit);