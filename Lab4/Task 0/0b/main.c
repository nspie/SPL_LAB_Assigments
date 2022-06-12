#include "util.h"
extern int system_call();

#define SYS_WRITE 4
#define STDOUT 1
#define SYS_LSEEK 19

int main (int argc , char* argv[], char* envp[])
{
  char * name = argv[2];
  int fileName = system_call(5, argv[1], 1, 0777);
  system_call(SYS_LSEEK,fileName,657,0); 
  system_call(SYS_WRITE, fileName, name, strlen(name));
  system_call(SYS_WRITE, fileName, ".\n\0", 3);
  system_call(6, fileName);	
  return 0;
}

