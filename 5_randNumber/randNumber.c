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


struct my_device_data {
    unsigned int seed;
    int config_option;
    char buffer[1024];
};

static int randOpen(struct inode *inode, struct file *filp) {
    struct my_device_data *my_data = kmalloc(sizeof(struct my_device_data), GFP_KERNEL);
    if (!my_data) {
        printk(KERN_ALERT "Failed to allocate memory for device data\n");
        return -ENOMEM;
    }

    my_data->seed = 12345;
    my_data->config_option = 0;

    filp->private_data = my_data;

    printk(KERN_ALERT "Device opened successfully\n");

    return RC_SUCCESS;
}

static int randClose(struct inode *inode, struct file *filp){
       struct my_device_data *my_data = filp->private_data;
       kfree(my_data);
       printk(KERN_ALERT "Device closed\n");
       return RC_SUCCESS;
}

static ssize_t randRead(struct file *filp, char __user *buf, size_t count, loff_t *f_pos){
    struct my_device_data *my_data = filp->private_data;
    ssize_t bytes_read = 0;
    ssize_t bytes_to_read;

    // Verifica si ya hemos llegado al final del archivo
    if (*f_pos >= sizeof(my_data->buffer))
        return 0; // Ya no hay más números aleatorios para leer

    // Calcula cuántos bytes se pueden leer en esta llamada
    bytes_to_read = min_t(ssize_t, count, sizeof(my_data->buffer) - *f_pos);

    // Genera números aleatorios y colócalos en el búfer del dispositivo
    get_random_bytes(my_data->buffer + *f_pos, bytes_to_read);

    // Copia los números aleatorios generados al espacio de usuario
    if (copy_to_user(buf, my_data->buffer + *f_pos, bytes_to_read)) {
        return -EFAULT; // Error de copia al espacio de usuario
    }

    // Actualiza la posición del archivo
    *f_pos += bytes_to_read;

    // Registra la cantidad de bytes leídos
    bytes_read = bytes_to_read;

    return bytes_read;

}


struct file_operations rand_fops = {
    .owner = THIS_MODULE,
    .open = randOpen,
    .release = randClose,
    .read = randRead,
};


static int hellostart(void){
    
    int rc;

    printk(KERN_ALERT"Inserting randDriver\n");

    // Dinamyc registration
    rc = register_chrdev(module_major, "randDriver", &rand_fops);

    // ERROR
    if(rc < 0)
        return rc;
    if(module_major == 0)
        module_major = rc;
    
    return RC_SUCCESS;
}

static void helloexit(void){
    printk(KERN_ALERT "Removing randDriver %d\n", module_major);
    unregister_chrdev(module_major, "randDriver");
}




module_init(hellostart);
module_exit(helloexit);
