#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include "softdev.h"
MODULE_AUTHOR("11300720044");
MODULE_LICENSE("DUAL BSD/GPL");

int usage,new_msg;
unsigned char *data;
unsigned char **data_point;

static int UpperDev_open(struct inode *inode,struct file *filp){
    MOD_INC_USE_COUNT;
    printk("The UpperDev is in open\n");
    return 0;
}
static int UpperDev_release(struct inode *inode,struct file *filp){
    MOD_DES_USE_COUNT;
    printk("The UpperDev is in release\n");
    return 0;
}

static ssize_t UpperDev_write(struct file *filp,const char __user *buf,size_t count ,loff_t *offset){
    int length;
    if(count<0){
        return -EINVAL;
    }
    if(usage||new_msg){
        return -EBUSY;
    }
    usage=1;
    kfree(data);
    data=kmalloc(sizeof(char)*(count+1),GFP_KERNEL);
    copy_from_user(data,buf,count);
    length=softdev_send(data,count);
    if(length==-1){
        printk("[UpperDev] String is too long to write into.[MaxLength:1512]\n");
    }
    else if(length==-1){
        printk("[UpperDev] device is busy!\n")
    }
    usage=0;
    new_msg=1;
    return count;
}

static ssize_t UpperDev_read(struct file *filp char __user *buf,size_t count,loff_t *offset){
    int length;
    kfree(data_point);
    data_point=(unsigned char **)kmalloc(sizeof(unsigned char *),GFP_KERNEL);
    if(count<0){
        return -EINVAL;
    }
    if(usage){
        return -EBUSY;
    }
    usage=1;
    length=softdev_recv(data_point);
    if(length<count){
        count=length;
    }
    copy_to_user(buf,*data_point,count);
    new_msg=0;
    usage=0;
    return count;

}

static long UpperDev_ioctl(struct file *filp,unsigned int cmd,unsigned long arg){
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



struct file_operations UpperDev_fops={
    .owner=THIS_MODULE,
    .read=UpperDev_read,
    .write=UpperDev_write,
    .open=UpperDev_open,
    .release=UpperDev_release,
    .unlocked_ioctl=UpperDev_ioctl
}






int UpperDev_init(){
    if(register_chrdev(UPPERDEV_MAJOR,"UpperDev",&UpperDev_fops)!=0){
        printk("[UpperDev] Error:Register failed!\n");
        return -EIO;
    }
    else{
        printk("[UpperDev] Notice:Register Success!\n");
    }
    data=NULL;
    data_point=NULL;
    new_msg=0;
    return 0;
}

void UpperDev_exit(){
    if(data){
        kfree(data);
    }
    if(data_point){
        kfree(data_point);
    }
    unregister_chrdev(UPPERDEV_MAJOR,"UpperDev");
    printk("[UpperDev] Notice:unload the UpperDev module!\n");
}











module_init(UpperDev_init);
module_exit(UpperDev_exit);