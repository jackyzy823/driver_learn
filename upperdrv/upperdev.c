#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
// #include <linux/syscalls.h> // to call sys_mknod
// #include <asm/io.h>
// #include <asm/system.h>
// #include <asm/uaccess.h>
#include <linux/cdev.h>//to import MKDEV
#include <linux/fs.h>  //to import register_chrdev_region and unreg~
#include "softdev.h"
#include <asm/io.h>
#include <asm/uaccess.h>

// #define UPPERDEV_MAJOR 117

static int UpperDev_major=UPPERDEV_MAJOR;

struct UpperDev *UpperDev_devp;

struct UpperDev{
    struct cdev cdev;
    // long count;
};



//static
extern long UpperDev_ioctl(struct file *filp,unsigned int cmd,unsigned long arg){
    switch(cmd){
        case 0:
            softdev_ioctl(0);
            printk(KERN_NOTICE "UpperDev use Lower");
            break;
        case 1:
            softdev_ioctl(1);
            printk(KERN_NOTICE "UpperDev use Upper");
            break;
        default:
            softdev_ioctl(1);
            printk(KERN_NOTICE "UpperDev use Upper");
            break;
    }
    return 1;
}


static const struct file_operations UpperDev_fops=
{
    .owner=THIS_MODULE,
    .unlocked_ioctl=UpperDev_ioctl,
    //above linux 2.6.38 ioctl =>unlocked_ioctl
    // .read=UpperDev_read,
    // .write=UpperDev_write,
    
};



static void UpperDev_setup_cdev(struct UpperDev *dev,int minor){
    int err;
    dev_t devno=MKDEV(UpperDev_major,minor);
    cdev_init(&dev->cdev,&UpperDev_fops);
    dev->cdev.owner=THIS_MODULE;
    dev->cdev.ops=&UpperDev_fops;
    err=cdev_add(&dev->cdev,devno,1);
    if(err){
        printk(KERN_NOTICE "ERROR IN cdev_add()\n");
    }

}



int UpperDev_init(void){
    int result;
    dev_t devno=MKDEV(UpperDev_major,0);
    result=register_chrdev_region(devno,1,"UpperDev");
    
    if(result<0){
        return result; //reg fail
    }
    printk(KERN_NOTICE "Start UP,Upper");
    //include <linux/syscalls.h>
    // sys_mknod("/dev/upper",O_RDWR | O_CREAT,UPPERDEV_MAJOR);
    UpperDev_setup_cdev(UpperDev_devp,0);
    return 0;

}

void UpperDev_exit(void){
    cdev_del(&UpperDev_devp->cdev);
    unregister_chrdev_region(MKDEV(UpperDev_major,0),1);
    printk(KERN_NOTICE "Terminate Down,Upper");
}



MODULE_AUTHOR("11300720044");
MODULE_LICENSE("DUAL BSD/GPL");
module_init(UpperDev_init);
module_exit(UpperDev_exit);
