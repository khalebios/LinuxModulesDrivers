
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h> //used for (un)register_chrdev()

#include  <linux/fs.h> //for copy to use

MODULE_AUTHOR("khalebios");
MODULE_DESCRIPTION("Drivers permettant d'ecrire sur un fichier");
MODULE_SUPPORTED_DEVICE("none");
MODULE_LICENSE("none");
#define DEVICE_NAME "khalebiosdriver"




static int buf_size = 64;
static char *buffer;

//ajout de paramettre d'entrée
//module_param(nom, type, permissions) 
//MODULE_PARM_DESC(nom, desc)

static int temperature;

module_param(temperature, int, 0);
MODULE_PARM_DESC(temperature, "parametre 1 de temperature");


///Driver en mode caractère
static int major = 0;//major=0 affectation dynamique dudriver


module_param(major, int, 0);
MODULE_PARM_DESC(major, "major number");

int ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);

int copy_from_user(unsigned long dest, unsigned long src, unsigned long len);
int copy_to_user(unsigned long dest, unsigned long src, unsigned long len);

static ssize_t my_read_function(struct file *file, char *buf, size_t count, loff_t *ppos)
{
    printk(KERN_DEBUG "read()\n");
/*Modification de la fonction Read */
	int lus = 0;

	printk(KERN_DEBUG "read: demande lecture de %d octets\n", count);
	/* Check for overflow */
	if (count <= buf_size - (int)*ppos)
		lus = count;
	else  lus = buf_size - (int)*ppos;
	if(lus)
		copy_to_user(buf, (int *)p->buffer + (int)*ppos, lus);
	*ppos += lus;
	printk(KERN_DEBUG "read: %d octets reellement lus\n", lus);
	printk(KERN_DEBUG "read: position=%d\n", (int)*ppos);
	return lus;
/*Find de la Modification de la fonction Read */
    return 0;
}

static ssize_t my_write_function(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
    printk(KERN_DEBUG "write()\n");
/*Modification de la fonction Write */
	int ecrits = 0;
	int i = 0;

	printk(KERN_DEBUG "write: demande ecriture de %d octets\n", count);
	/* Check for overflow */
	if (count <= buf_size - (int)*ppos)
		ecrits = count;
	else  ecrits = buf_size - (int)*ppos;

	if(ecrits)
		copy_from_user((int *)p->buffer + (int)*ppos, buf, ecrits);
	*ppos += ecrits;
	printk(KERN_DEBUG "write: %d octets reellement ecrits\n", ecrits);
	printk(KERN_DEBUG "write: position=%d\n", (int)*ppos);
	printk(KERN_DEBUG "write: contenu du buffer\n");
	for(i=0;i<buf_size;i++)
		printk(KERN_DEBUG " %d", p->buffer[i]);
	printk(KERN_DEBUG "\n");
	return ecrits;

/*Fin de la Modification de la fonction Read */
    //return 0;
}

static int my_open_function(struct inode *inode, struct file *file)
{
    printk(KERN_DEBUG "open()\n");
    return 0;
}

static int my_release_function(struct inode *inode, struct file *file)
{
    printk(KERN_DEBUG "close()\n");
    return 0;
}





int my_ioctl_function(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
    int retval = 0;
    
    switch(cmd)
    {
        case 1 : break;
        case 2 : break;
        default : retval = -EINVAL; break;
    }
    return retval;
}




static struct file_operations fops = 
{
    read : my_read_function,
    write : my_write_function,
    open : my_open_function,
    release : my_release_function, /* correspond a close */
ioctl : my_iotl_function
};


//function call when starting the module
static int __init mon_module_init(void)
{
    int ret;

    ret = register_chrdev(major, DEVICE_NAME, &fops);
    
    if(ret < 0)
    {
        printk(KERN_WARNING "Probleme sur le major: Chargement Impossible\n");
        return ret;
    }
    
    printk(KERN_DEBUG "khalebiosdriver loaded with Major Number = %d!!\n",ret);


    return 0;
}


//function call when exit the modul
static void __exit mon_module_cleanup(void)
{
   // int ret;
    //ret = 
unregister_chrdev(major, DEVICE_NAME);
 //< 0
unregister_chrdev(major, "khalebiosdriver");
printk(KERN_WARNING "Probleme unregister\n");
printk(KERN_DEBUG "khalebiosdriver unloaded!!\n");

}


module_init(mon_module_init);
module_exit(mon_module_cleanup);
