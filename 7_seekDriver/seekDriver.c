#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h> 

MODULE_LICENSE("GPL");

# define DEVICE_NAME "seekDriver"
static dev_t device_major;

struct my_device_data {
    char buffer[1024];
};

// For this driver, we will just alloc a buffer to our struct and initialize it.
static ssize_t driverWrite(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos){
    struct my_device_data *data = kmalloc(sizeof(struct my_device_data), GFP_KERNEL);
    int i = 0;

    if (!my_data) {
        printk(KERN_ALERT "Failed to allocate memory for device data\n");
        return -ENOMEM;
    }

    while(i < 1024){
        data->buffer[i] = i + 1;
        i ++;
    }

    if (! filp->private_data){
        filp->private_data = data;
        printk(KERN_INFO "Saved data!");
    }
    else{
        prink(KERN_INFO "Data was allready allocated!");
        kfree(data);
    }

    return 0;

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

    // Register a range of char device numbers. 
    if (alloc_chrdev_region(&device_major, 0, 1, DEVICE_NAME))
    {
        printk(KERN_ERR "Failed to allocate character device region\n");
        return -1;
    }

    // Creates device class
    if (!(mydev_class = class_create(THIS_MODULE, DEVICE_NAME)))
    {
        printk(KERN_ERR "Failed to create device class\n");
        unregister_chrdev_region(device_major, 1);
        return -1;
    }

    // Creates the device
    cdev_init(&mydev_cdev, &mydev_fops);
    if (cdev_add(&mydev_cdev, device_major, 1))
    {
        printk(KERN_ERR "Failed to add character device\n");
        class_destroy(mydev_class);
        unregister_chrdev_region(device_major, 1);
        return -1;
    }

    // Creates device on /dev
    device_create(mydev_class, NULL, device_major, NULL, "%s-%d", DEVICE_NAME, 0);

    printk(KERN_INFO "mydev module loaded\n");

}

static void driverExit (void){
    printk(KERN_INFO "Unregistering module with major %d", major);
    unregister_chrdev(major, "persistent");
}


module_init(driverInit);
module_exit(driverExit);