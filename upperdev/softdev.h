#ifndef _SOFTDEV_H
#define _SOFTDEV_H

extern int softdev_send(unsigned char *buff, int len);
extern int softdev_recv(unsigned char **p);
extern int softdev_ioctl(int cmd);
#define UPPERDEV_MAJOR	117

#endif

