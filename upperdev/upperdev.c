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

// static int UpperDev_major=UPPERDEV_MAJOR;

static unsigned int upperdev_inc=0;
char buffer[1512]={0};


////
// int usage,new_msg;
// unsigned char *data;
// unsigned char **data_point;
////
// struct UpperDev *UpperDev_devp;

// struct UpperDev{
//     struct cdev cdev;
//     // long count;
// };

int UpperDev_open(struct inode *inode,struct file *filp){
    if(upperdev_inc>0){
        return -ERESTARTSYS;
    }
    upperdev_inc++;
    return 0;
}

int UpperDev_release(struct inode *inode,struct file *filp){
    upperdev_inc--;
    return 0;
}


ssize_t UpperDev_read(struct file *filp,char __user *buf, size_t size, loff_t *ppos){
    printk(KERN_NOTICE "[UpperDev]IN UpperDev_read!");
    // int len=softdev_recv();
    // if(copy_to_user(buf,buffer,len)){
    //     return -EFAULT;
    // }
    return -EINVAL;
}

ssize_t UpperDev_write(struct file *filp,const char __user *buf ,size_t size,loff_t *ppos){
    printk(KERN_NOTICE "[UpperDev]IN UpperDev_write!");
    if(copy_from_user(buffer,buf,size)){
        softdev_send(buffer,size);
        return -EFAULT;
    }
    return -EINVAL;
}


//static
long UpperDev_ioctl(struct file *filp,unsigned int cmd,unsigned long arg){
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
    .read=UpperDev_read,
    .write=UpperDev_write,
    .open=UpperDev_open,
    .release=UpperDev_release,
    //above linux 2.6.38 ioctl =>unlocked_ioctl
    // .read=UpperDev_read,
    // .write=UpperDev_write,
    
};



// static void UpperDev_setup_cdev(struct UpperDev *dev,int minor){
//     int err;
//     dev_t devno=MKDEV(UpperDev_major,minor);
//     cdev_init(&dev->cdev,&UpperDev_fops);
//     dev->cdev.owner=THIS_MODULE;
//     dev->cdev.ops=&UpperDev_fops;
//     err=cdev_add(&dev->cdev,devno,1);
//     if(err){
//         printk(KERN_NOTICE "ERROR IN cdev_add()\n");
//     }

// }



// int UpperDev_init(void){
//     int result;
//     dev_t devno=MKDEV(UpperDev_major,0);
//     result=register_chrdev_region(devno,1,"UpperDev");
    
//     if(result<0){
//         return result; //reg fail
//     }
//     printk(KERN_NOTICE "Start UP,Upper");
//     //include <linux/syscalls.h>
//     // sys_mknod("/dev/upper",O_RDWR | O_CREAT,UPPERDEV_MAJOR);
//     // UpperDev_setup_cdev(UpperDev_devp,0);
//     return 0;

// }

// void UpperDev_exit(void){
//     cdev_del(&UpperDev_devp->cdev);
//     unregister_chrdev_region(MKDEV(UpperDev_major,0),1);
//     printk(KERN_NOTICE "Terminate Down,Upper");
// }

int UpperDev_init(void){
    int ret;
    ret=register_chrdev(UPPERDEV_MAJOR,"Upper",&UpperDev_fops);
    if(ret<0){
        printk("Unable to register char dev Upper");
        return ret;
    }
    return 0;
}

void UpperDev_exit(void){
    unregister_chrdev(UPPERDEV_MAJOR,"Upper");
    printk("Remove Upper");
}



MODULE_AUTHOR("11300720044");
MODULE_LICENSE("DUAL BSD/GPL");
module_init(UpperDev_init);
module_exit(UpperDev_exit);
