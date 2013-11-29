#include <linux/module.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/kernel.h>

#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/termios.h>
#include <linux/in.h>
#include <linux/fcntl.h>
#include <linux/inet.h>
#include <linux/netdevice.h>
#include <net/ip.h>
#include <net/protocol.h>
#include <net/icmp.h>
#include <net/tcp.h>
#include <linux/skbuff.h>
#include <net/sock.h>
#include <linux/timer.h>
#include <linux/version.h>

int _data_OK = 0;
unsigned char _data_buff[1512];
int _data_len = 0;
int work=1;

unsigned int _softdev_irq = 0;
void (*_i_handler)(int, void *, struct pt_regs *)=NULL;
struct net_device *_softdev_dev;
struct pt_regs _pseudo_regs;

/*
void loopdrv_interrupt(int irq, void *dev_id, struct pt_regs * regs)
{
}
*/
void toupper(char *src, char *dest, int len)
{
	int i;
	for(i=0;i<len;i++)
	{	if(*(src+i)>='a' && *(src+i)<='z')
			*(dest+i) = *(src+i)+'A'-'a';
		else
			*(dest+i) = *(src+i);
	}
}

int softdev_send(unsigned char *buff, int len)
{
	if(len>1512)
		return -1;
	if(_data_OK)
		return -2;	/* Busy */
	if(work)
		toupper(buff, _data_buff,len);
	else
		memcpy(_data_buff,buff,len);
	_data_len = len;
	_data_OK = 1;
	if(_i_handler)
		_i_handler(_softdev_irq, (void*)_softdev_dev, &_pseudo_regs);
	return len;
}

int softdev_recv(unsigned char **p)
{
	if(_data_OK)
	{	*p = _data_buff;
		_data_OK = 0;
		return _data_len;
	}
	*p = NULL;
	return 0;
}

void softdev_ioctl(int cmd)
{
	work = cmd;
}

int softdev_init(unsigned int irq, void (*handler)(int, void *, struct pt_regs *), struct net_device *dev)
{
	_softdev_irq = irq;
	_i_handler = handler;
	_softdev_dev = dev;
	return 0;
}

EXPORT_SYMBOL(softdev_send);
EXPORT_SYMBOL(softdev_recv);
EXPORT_SYMBOL(softdev_ioctl);
EXPORT_SYMBOL(softdev_init);

int init_softdev(void)
{
	return 0;
}

void cleanup_softdev(void)
{
}
module_init(init_softdev);
module_exit(cleanup_softdev);
MODULE_AUTHOR("Fudan");
MODULE_DESCRIPTION("Softdev virtual device");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
