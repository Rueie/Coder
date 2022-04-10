#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char* argv[]){
    char buffer[BUFSIZ+1];
    memset(buffer,0,strlen(buffer));
    FILE* file=fopen(argv[1],"rb");
    int number_of_bytes;
    if(file!=NULL){
        number_of_bytes=fread(buffer,sizeof(char),BUFSIZ,file);
        if(number_of_bytes>0){
            buffer[number_of_bytes-1]='\0';
            fwrite(buffer,sizeof(char),strlen(buffer),stdout);
        }
    }

    return 0;
}
