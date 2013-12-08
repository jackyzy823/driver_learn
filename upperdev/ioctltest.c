//ioctltest
/*
*Author="11300720044"
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

int main(int argc,char* argv[]){
    int fd;
    unsigned int cmd;
    // printf("%d\n",argc);
    if(argc!=3){
        printf("Wrong arguments.Please input filename/devname and command.\nSuch as ./ioctltest /dev/upper 1\n");
        return -1;
    }
    fd=open(argv[1],O_RDONLY);
    cmd=atoi(argv[2]);
    if(cmd==1||cmd==0){
        ioctl(fd,cmd);
        printf("%s\n", cmd==1?"Change to Upper":"Change to Lower");
        return 0;
    }
    else{
        printf("Wrong cmd\n");
        return -1;
    }

}