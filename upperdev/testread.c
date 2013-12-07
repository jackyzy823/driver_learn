/*
filename:testread.c
function:read data from upper
usage:./testread upper
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int argc ,char * argv[]){
    int fd,readres;
    char buffer[2048]={0};
    if(argc!=2){
      printf("Please input filename.Such as ./testread /dev/upper\n");
      return -1;
    }
    fd=open(argv[1],O_RDONLY);
    if(fd==-1){
      printf("Cannot open file,Please retry\n");
      return -1;
    }
    // printf("%d\n",fd);
    // while(1){
    readres=read(fd,buffer,2048);
    if(readres!=-1){
      printf("%s\n", buffer);      
    }
    close(fd);
    return 0;
    // }
    // printf("%d\n",argc);
    // for(i=1;i<argc;i++){
    //     printf("argv[%d]:%s\n",i,argv[i]);
    // }
    // return 0;
}
