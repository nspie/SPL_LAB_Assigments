#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 32

int main(int argc, char** argv) {
  char buffer[BUFFER_SIZE];
  int p[2];
  char* msg = "hello";
  pid_t pid;

  /*cleaning the buffer*/
  for (int i = 0; i < BUFFER_SIZE; i++)
    buffer[i] = 0;

  
  if (pipe(p) == -1){
      perror("pipe didn't succeed");
      exit(EXIT_FAILURE);
  }
  
  pid = fork();
  
    if (pid == -1){
        perror("fork didn't succeed");
        exit(EXIT_FAILURE);
    }
  
  if (pid > 0)  {    
    close(p[0]);
    write(p[1], msg, strlen(msg));
    close(p[1]);
  }
  
  else {
    close(p[1]);
    read(p[0], buffer, strlen(msg));
    printf("%s\n", buffer);
    close(p[0]);
  }
  
  return 0;
}
