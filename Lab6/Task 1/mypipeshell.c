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



int cd_cmd(cmdLine* command, int debug){
    
  int cd = 0;
    
  if(strcmp(command->arguments[0],"cd") == 0){
      
    cd = 1;
        
    int val = chdir(command->arguments[1]);
    
    if(val < 0){
      perror("ERROR on cd command");
    
    if(debug)
        fprintf(stderr, "%s\n","ERROR on cd command");

    }
  }

  return cd;
}

void pipe_cmd(cmdLine* command, int debug){
    
    int val;
    pid_t child1_pid, child2_pid;

    int p[2]; 
    
    if (pipe(p) == -1){
        perror("pipe didn't succeed");
        exit(EXIT_FAILURE);
    }
    
    print_debug("parent_process>forking...", -1, debug);
    
    child1_pid = fork();
  
    if (child1_pid == -1){
        perror("fork1 didn't succeed");
        _exit(EXIT_FAILURE);
    }
    
    print_debug("parent_process>created process with id", getpid(), debug);
    
        /*child1*/
        if (child1_pid == 0){
            
            print_debug("child1>redirecting stdout to the write end of the pipe...", -1, debug);
            
            close(STDOUT);
            dup(p[1]);
            close(p[1]);
            print_debug("child1>going to execute cmd: ...", -1, debug);
             
            val = execvp(command->arguments[0] , command->arguments);
                
            if(val < 0){
            perror("Could not execute the command");
            _exit(EXIT_FAILURE);
            }            

        }
    
        else {
            print_debug("parent_process>closing the write end of the pipe...", -1, debug);
            
            close(p[1]);
            print_debug("parent_process>forking...", -1, debug);
            child2_pid = fork();
            
            if (child2_pid == -1){
                perror("fork2 didn't succeed");
                exit(EXIT_FAILURE);
            }
            
            print_debug("parent_process>created process with id", getpid(), debug);
            
            /*child2*/
            if(child2_pid == 0){
                print_debug("child2>redirecting stdin to the read end of the pipe...", -1 , debug);
                
                close(STDIN);
                dup(p[0]);
                close(p[0]);
                
                print_debug("child2>going to execute cmd: ...", -1 , debug);
                
                val = execvp(command->next->arguments[0] , command->next->arguments);
                
                  if(val < 0){
                    perror("Could not execute the command");
                    _exit(EXIT_FAILURE);
                    }
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
    
}


void execute(cmdLine* pCmdLine, int debug){
    
    int input = STDIN;
    int ouput = STDOUT;
    pid_t pid;
    int val = 0;

    
    if(cd_cmd(pCmdLine, debug) == 0){

	  if(strcmp(pCmdLine->arguments[0],"quit") == 0){
        freeCmdLines(pCmdLine);
		_exit(EXIT_SUCCESS);
      }
      

          
        if(pCmdLine->inputRedirect){
            close(input);
            if(!fopen(pCmdLine->inputRedirect, "r")){
                perror("Error");
                exit(EXIT_FAILURE);
            }
		}
		
		
        if(pCmdLine->outputRedirect){
            close(ouput);
            if(!fopen(pCmdLine-> outputRedirect, "w+")){
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }
        
        
        if(pCmdLine->next != NULL){
            pipe_cmd(pCmdLine, debug);
        }
        
        else{
            pid_t pid = fork();
            if (pid == 0)
                val = execvp(pCmdLine->arguments[0],pCmdLine->arguments);
            if(val < 0){
                perror("Could not execute the command");
                _exit(EXIT_FAILURE);
            }
            

            
        }
                
      

	  if(debug){
	  	fprintf(stderr, "%s","PID: ");
		fprintf(stderr, "%d\n",pid);
		fprintf(stderr, "%s","Executing command: ");
		fprintf(stderr, "%s\n",pCmdLine->arguments[0]);
	  }

	    if(pCmdLine->blocking)  
		waitpid(pid, NULL, 0);

    }

}


int main(int argc, char const *argv[]) {
    
	int debug = 0;
	int i;

  	for (i = 1; i < argc; i++){
      
  		if (strncmp("-d", argv[i], 2) == 0)
			debug = 1;

	}
	
	
    char buf[BUFFER_SIZE];

	  while(1){

		    printCWD();
		    fgets(buf,BUFFER_SIZE,stdin);
		    cmdLine* line = parseCmdLines(buf);
		    execute(line, debug);
		    freeCmdLines(line);
		    fprintf(stdout, "%c",'\n');
	  }

  return 0;
  
}
