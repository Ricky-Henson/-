#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

// ./a.out reserve reserve.txt
int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "usage: %s sourceFile targetFile\n", argv[0]);
        exit(1);
    }
    char *buf;
    int file, fileSize=0, i;
    struct stat stbuf;
    if((strcmp(argv[1], "reserve") == 0)){
        if((file = open(argv[2], O_RDONLY, 0600)) < 0){
            perror("open");
        }
    }
    else{
        fprintf(stderr, "invalid command '%s'\n", argv[1]);
        exit(1);
    }
    fstat(file, &stbuf);
    fileSize = stbuf.st_size;
    buf = (char *) malloc (fileSize + 1);
    read(file, buf, fileSize);
    close(file);
    // buf[0] = 'a';
    // printf("%c\n", buf[0]);
    char *newbuf = (char *) malloc (fileSize + 1);
    int len = strlen(buf);
    char *ptr = buf;
    // while(*ptr){
    //     ptr++;
    // }
    // ptr--;
    ptr+=(len-1);
    char *qtr = newbuf;
    for(i=(len-1); i>=0; i--){
        *qtr++ = *ptr--;
    }
    *qtr = '\0';
    // printf("%s\n", newbuf);
    if((file = open(argv[2], O_WRONLY, 0600)) < 0){
        perror("open");
    }
    write(file, newbuf, fileSize);
    close(file);

    return 0;
}
