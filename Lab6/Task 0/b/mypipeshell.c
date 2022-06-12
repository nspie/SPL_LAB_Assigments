#include "LineParser.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#define BUFFER_SIZE 2048
#define STDIN 0
#define STDOUT 1

void print_debug(char *msg, int pid, int debug){
    
    if(debug){
        
        if (pid != -1)
            fprintf(stderr, "(%s: %d)\n", msg, pid);
        
        else
            fprintf(stderr, "(%s)\n", msg);    
        }
}


void printCWD(){
  char path_name[PATH_MAX];
  getcwd(path_name,PATH_MAX);
  fprintf(stdout, "%s\n",path_name);
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
		_exit(EXIT_SUCCESS);

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
    pid_t child1_pid, child2_pid;


  	for (i = 1; i < argc; i++){
      
  		if (strncmp("-d", argv[i], 2) == 0)
			debug = 1;

	}
		
    char* const ls[3] = {"ls","-l",0};
    char* const tail[4] = {"tail","-n","2",0};
    int p[2]; 
    
    if (pipe(p) == -1){
        perror("pipe didn't succeed");
        exit(EXIT_FAILURE);
    }
    
    print_debug("parent_process>forking...", -1, debug);
    
    child1_pid = fork();
  
    if (child1_pid == -1){
        perror("fork1 didn't succeed");
        exit(EXIT_FAILURE);
    }
    
    print_debug("parent_process>created process with id", getpid(), debug);
    
        /*child1*/
        if (!child1_pid){
            
            print_debug("child1>redirecting stdout to the write end of the pipe...", -1, debug);
            close(STDOUT);
            
            dup(p[1]);
            close(p[1]);
            print_debug("child1>going to execute cmd: ...", -1, debug);
            execvp(ls[0] , ls);
            
            perror("Error");
            exit(EXIT_FAILURE);
    }
    
    
    
        else {
            print_debug("parent_process>closing the write end of the pipe...", -1, debug);
            close(p[1]);
            
            print_debug("parent_process>forking...", -1, debug);
            child2_pid = fork();
            
            if (child2_pid == -1){
                perror("Error");
                _exit(EXIT_FAILURE);
            }
            
            print_debug("parent_process>created process with id", getpid(), debug);
            
            /*child2*/
            if(!child2_pid){
                print_debug("child2>redirecting stdin to the read end of the pipe...", -1 , debug);
                close(STDIN);
                
                dup(p[0]);
                close(p[0]);
                
                print_debug("child2>going to execute cmd: ...", -1 , debug);
                execvp(tail[0],tail);
                
                perror("Error");
                exit(EXIT_FAILURE);
            }
            
            else {
                
            print_debug("parent_process>closing the read end of the pipe...", -1 , debug);
            close(p[0]);
            
            print_debug("parent_process>waiting for child processes to terminate...", -1 , debug);
            waitpid(child1_pid, NULL, 0);
            
            print_debug("parent_process>waiting for child processes to terminate...", -1 , debug);
            waitpid(child2_pid,NULL,0);
            
            }
      }
      
        print_debug("parent_process>closing the read end of the pipe", -1, debug);
        print_debug("parent_process>exiting...", -1, debug);


  return 0;
}
