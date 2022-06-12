#include "util.h"
extern int system_call();

#define SYS_WRITE 4
#define STDOUT 1
#define SYS_LSEEK 19

int main (int argc , char* argv[], char* envp[])
{
  char * name = argv[2];
  char * fileName = system_call(5, argv[1], 1, 0777);
  system_call(SYS_LSEEK,fileName,  0, 657); 
  system_call(SYS_WRITE, fileName, name, strlen(name));
  system_call(SYS_WRITE, fileName, ".     ", 6);
/*

  system_call(SYS_WRITE,STDOUT, str,strlen(str));
  for (i = 0 ; i < argc ; i++)
    {
      system_call(SYS_WRITE,STDOUT,"argv[", 5);
	  str = itoa(i);
      system_call(SYS_WRITE,STDOUT,str,strlen(str));
      system_call(SYS_WRITE,STDOUT,"] = ",4);
      system_call(SYS_WRITE,STDOUT,argv[i],strlen(argv[i]));
      system_call(SYS_WRITE,STDOUT,"\n",1);
    }
*/
  return 0;
}

