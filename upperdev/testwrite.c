/*
filename:testwrite.c
function:write data to upper
usage:./testwrite upper  aaaaa
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char* argv[]){
    int fd,writeres;
    char buffer[2048]={0};
    if(argc!=3){
        printf("Wrong Arguments.Please do like this ./testwrite /dev/upper  helloworld!\n");      
        return -1;
    }
    fd=open(argv[1],O_WRONLY);
    if(fd==-1){
        printf("Fail to open file\n");
        return -1;
    }

    writeres=write(fd,argv[2],strlen(argv[2]));
    close(fd);


}
