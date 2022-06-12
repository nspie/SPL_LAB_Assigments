#include "LineParser.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 2048

void printCWD(){
  char path_name[PATH_MAX];
  getcwd(path_name,PATH_MAX);
  fprintf(stdout, "%s>",path_name);
}



int CDCommand(cmdLine* command, int debug){
    
  int cd = 0;
    
  if(strcmp(command->arguments[0],"cd") == 0){
      
    cd = 1;
        
    int val = chdir("..");
    
    if(val < 0){
      perror("ERROR on cd command");
    
    if(debug)
        fprintf(stderr, "%s\n","ERROR on cd command");

    }
  }

  return cd;
}




void execute(cmdLine* pCmdLine, int debug){
    
    if(CDCommand(pCmdLine, debug) == 0){

	  if(strcmp(pCmdLine->arguments[0],"quit") == 0)
		exit(EXIT_SUCCESS);

	    pid_t pid = fork();
	    int val = 0;

	  if (pid == 0){ 
		val = execvp(pCmdLine->arguments[0],pCmdLine->arguments);
		}

	  if(debug){
	  	fprintf(stderr, "%s","PID: ");
		fprintf(stderr, "%d\n",pid);
		fprintf(stderr, "%s","Executing command: ");
		fprintf(stderr, "%s\n",pCmdLine->arguments[0]);

	  }

	    if(pCmdLine->blocking)  
		waitpid(pid, NULL, 0);


	  if(val < 0){
		perror("Could not execute the command");
		_exit(EXIT_FAILURE);
	  }
    }

}

int main(int argc, char const *argv[]) {
	int debug = 0;
	int i;

  	for (i = 1; i < argc; i++){
      
  		if (strncmp("-d", argv[i], 2) == 0)
			debug = 1;

	}

	  FILE* input = stdin;
	  char buf[BUFFER_SIZE];

	  while(1){

		    printCWD();
		    fgets(buf,BUFFER_SIZE,input);
		    cmdLine* line = parseCmdLines(buf);
		    execute(line, debug);
		    freeCmdLines(line);
		    fprintf(stdout, "%c",'\n');


	  }

  return 0;
}
