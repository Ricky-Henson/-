#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h> // O_CREAT O_WRONLY O_RDONLY O_EXCL O_RDWR
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
    char *buf;
    int file, fileSize=0;
    struct stat stbuf;
    if(argc != 3){
        fprintf(stderr, "usage: %s sourceFile targetFile\n", argv[0]);
        exit(1);
    }
    if(strcmp(argv[1], "tolower") == 0){
        if((file = open(argv[2], O_RDONLY | O_CREAT, 0600)) < 0){ // if fail to open
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
    // printf("%s\n", buf);
    char *ptr = buf;
    while(*ptr){
        if(isupper(*ptr)){
            *ptr+=32;
            // printf("%c\n", *ptr);
        }
        ptr++;
    }
    *ptr = '\0';
    // strlwr not working?
    // printf("%s\n", buf);
    if((file = open(argv[2], O_WRONLY, 0600)) < 0){
        perror("open");
    }
    write(file, buf, fileSize);
    close(file);

    return 0;
}
