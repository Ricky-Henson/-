#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h> // O_CREAT O_WRONLY O_RDONLY O_EXCL O_RDWR
#include<unistd.h> // read(), write(), close()
#include<sys/stat.h> // fstat
// Note : O_EXCL if file exists, nothing u can do
// O_APPEND (concatenate)

// ./a.out copy.txt anyfile.txt
int main(int argc, char* argv[]){
  char *buf;
  int file2, file1, filesize;
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
    filesize = stbuf.st_size;
    buf = (char *) malloc (filesize +1);
    read(file1, buf, filesize);
    // printf("%s\n", buf);
    write(file2, buf, filesize);
    close(file1); close(file2);
  }
//   else{
//       printf("%s doesn't exist\n", argv[1]);
//       exit(1);
//   }
  return 0;
}
