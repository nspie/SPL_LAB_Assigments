#include "util.h"
extern int system_call();

#define SYS_WRITE 4
#define SYS_READ 3
#define STDOUT 1
#define SYS_LSEEK 19
#define STDIN 0
#define STDERR 2
int main (int argc , char* argv[], char* envp[])
{
  int debug = 0;
  if (argc > 1)
	if (strncmp("-D", argv[1], 2)==0)
		debug = 1;
  char currC[1];
  int toPrint = system_call(SYS_READ, STDIN,currC, 1); 	
  if (debug){
	system_call(SYS_WRITE,STDERR,itoa(SYS_READ), 1);
	system_call(SYS_WRITE,STDERR,":", 1);
	system_call(SYS_WRITE,STDERR,itoa(toPrint), 1);
	system_call(SYS_WRITE,STDERR,":", 1);
	system_call(SYS_WRITE,STDERR,&currC, 1);
	system_call(SYS_WRITE,STDERR,"\n", 1);
  }
  int waitForSpace = 0;
  int counter = 0;
  while (toPrint > 0){
	while (currC[0] != '\n'){
	    	if (currC[0] == ' '){
			if (waitForSpace)
				waitForSpace = 0;		 
		}

		else {
			if (!waitForSpace){
				counter++;
				waitForSpace = 1;
			}
		} 
		toPrint = system_call(SYS_READ, STDIN,currC, 1);
		if (debug){
			system_call(SYS_WRITE,STDERR,itoa(SYS_READ), 1);
			system_call(SYS_WRITE,STDERR,":", 1);
			system_call(SYS_WRITE,STDERR,itoa(toPrint), 1);
			system_call(SYS_WRITE,STDERR,":", 1);
			system_call(SYS_WRITE,STDERR,&currC, 1);
			system_call(SYS_WRITE,STDERR,"\n", 1);
	  	} 	

  	}
	waitForSpace = 0;
	toPrint = system_call(SYS_READ, STDIN,currC, 1);
	if (debug){
		system_call(SYS_WRITE,STDERR,itoa(SYS_READ), 1);
		system_call(SYS_WRITE,STDERR,":", 1);
		system_call(SYS_WRITE,STDERR,itoa(toPrint), 1);
		system_call(SYS_WRITE,STDERR,":", 1);
		system_call(SYS_WRITE,STDERR,&currC, 1);
		system_call(SYS_WRITE,STDERR,"\n", 1);
	  	}
  }
  
	system_call(SYS_WRITE,STDOUT,itoa(counter), 1);
	system_call(SYS_WRITE,STDOUT,"\n", 1);
  return 0;
}

