#include "util.h"
extern int system_call();

#define SYS_WRITE 4
#define SYS_READ 3
#define STDOUT 1
#define SYS_LSEEK 19
#define STDIN 0
#define STDERR 2
#define SYS_OPEN 5

int sysWrite(int output, char* sentance, int length, int debug){
	int retVal = 0;
	retVal = system_call(4, output, sentance, length);
	system_call(4, output, "\n",1);
	if (debug == 1){
		system_call(SYS_WRITE,STDERR,itoa(SYS_WRITE), 1);
		system_call(SYS_WRITE,STDERR,":", 1);
		system_call(SYS_WRITE,STDERR,itoa(retVal), 1);
		system_call(SYS_WRITE,STDERR,":", 1);
		system_call(SYS_WRITE,STDERR,"\n", 1);
	}
	return retVal;
}
int sysRead(int input, char* buff, int length, int debug){
	int retVal = system_call(3, input, buff, length);
	if (debug == 1){
		system_call(SYS_WRITE,STDERR,itoa(SYS_READ), 1);
		system_call(SYS_WRITE,STDERR,":", 1);
		system_call(SYS_WRITE,STDERR,itoa(retVal), 1);
		system_call(SYS_WRITE,STDERR,":", 1);
		system_call(SYS_WRITE,STDERR,buff, 1);
		system_call(SYS_WRITE,STDERR,"\n", 1);
	}
	return retVal;
}
int sysOpen(char* fileName, int mode, int mode2, int debug){
	int retVal = system_call(5, fileName, mode, mode2);
	if (debug == 1){
		system_call(SYS_WRITE,STDERR,itoa(SYS_OPEN), 1);
		system_call(SYS_WRITE,STDERR,":", 1);
		system_call(SYS_WRITE,STDERR,itoa(retVal), 1);
        system_call(SYS_WRITE,STDERR,"\n", 1);
	}
	return retVal;
}


int main (int argc , char* argv[], char* envp[])
{
  int input = STDIN;
  int output = STDOUT;
  int debug = 0;
  int i;
  for (i = 1; i<argc; i++){
  	if (strncmp("-D", argv[i], 2)==0)
		debug = 1;
	else if (strncmp("-i", argv[i], 2)==0)
		input = sysOpen(argv[i]+2, 0, 0777, debug);
	else if (strncmp("-o", argv[i], 2)==0)
		output = sysOpen(argv[i]+2,64 | 1, 0777, debug);

  }
  char currC[1];
  int toPrint = sysRead(input,currC, 1, debug); 	
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
		toPrint = sysRead(input,currC, 1, debug);

  	}
	waitForSpace = 0;
	toPrint = sysRead(input,currC, 1, debug);
  }
	char *countPointer = itoa(counter);
	sysWrite(output,countPointer, strlen(countPointer), debug);
    if (output != STDOUT)
        system_call(6,output);
    if (input != STDIN)
        system_call(6, input);
  return 0;
}
