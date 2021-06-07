#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h> // O_CREAT O_RDWD
#include<unistd.h> // read(), write(), close()
#include<sys/stat.h> // fstat
// Note : O_EXCL if file exists, nothing u can do
// O_APPEND | O_RDWR
int main(int argc, char* argv[]){
  char *buf;
  int file2, file1,fileread;
  struct stat stbuf;
  // output file opened or created
  if(argc != 3){
      fprintf(stderr, "usage: %s sourceFile targetFile\n", argv[0]);
      exit(1);
  }
  if((file2 = open(argv[2], O_CREAT | O_WRONLY, 0600)) < 0){ // if fail to open
    perror("open");
  }
  // lets open the input file
  file1 = open(argv[1], O_RDONLY);
  if(file1 < 0){ // another wat to express 'fail to open'
      fprintf(stderr, "open error: %s\n", argv[1]);
      exit(1);
  }
  else{ // there are things to read from the input
    fstat(file1, &stbuf);
    fileread = stbuf.st_size;
    buf = (char *) malloc (fileread +1);
    fileread = read(file1, buf, fileread);
    // printf("%s\n", buf);
    write(file2, buf, fileread);
    close(file1);
  }
//   else{
//       printf("%s doesn't exist\n", argv[1]);
//       exit(1);
//   }
  close(file2);
  return 0;
}
