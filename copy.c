 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
// Note : O_EXCL if file exists, nothing u can do
// O_APPEND | O_RDWR
int main(int argc, char* argv[]){
  char buf[1024];
  int file2, file1,fileread;
  // output file opened or created
  if(argc != 3){
      fprintf(stderr, "usage: %s sourceFile targetFile\n", argv[0]);
      exit(1);
  }
  if((file2 = open(argv[2], O_CREAT | O_WRONLY, 0600))==-1){ // if fail to open
    perror("open");
  }
  // lets open the input file
  file1 = open(argv[1], O_RDONLY);
  if(file1 < 0){ // another wat to express 'fail to open'
      fprintf(stderr, "open error: %s\n", argv[1]);
      exit(1);
  }
  else{ // there are things to read from the input
    fileread = read(file1, buf, sizeof(buf) + 1); // avoid buffer overflow
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
