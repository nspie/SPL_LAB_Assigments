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



/*given function*/



int ** createPipes(int nPipes){

    int** pipes;

    pipes=(int**) calloc(nPipes, sizeof(int));



    for (int i=0; i<nPipes;i++){

        pipes[i]=(int*) calloc(2, sizeof(int));

        pipe(pipes[i]);

    }  

    return pipes;


    }



void releasePipes(int **pipes, int nPipes){

        for (int i=0; i<nPipes;i++){

            free(pipes[i]);

        

        }  

    free(pipes);

}





int *leftPipe(int **pipes, cmdLine *pCmdLine){

    if (pCmdLine->idx == 0) return NULL;

    return pipes[pCmdLine->idx -1];

}







int *rightPipe(int **pipes, cmdLine *pCmdLine){

    if (pCmdLine->next == NULL) return NULL;

    return pipes[pCmdLine->idx];

}


/* end of given functions*/



void print_debug(char *msg, int pid, int debug){
    
    if(debug){
        
        if (pid != -1)
            fprintf(stderr, "(%s: %d)\n", msg, pid);
        
        else
            fprintf(stderr, "(%s)\n", msg);    
        }
}

int count_pipes(cmdLine* line){
    
        int counter = -1;
        cmdLine* curr = line;
        
		while(curr != NULL){
			counter++;
			curr = curr->next;
		}
		
		return counter;
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
            

void execute(cmdLine* pCmdLine, int debug){
    
    int input = STDIN;
    int output = STDOUT;
    pid_t pid;
    int val = 0;
    int fd_input, fd_output;

    
    if(cd_cmd(pCmdLine, debug) == 0){

	  if(strcmp(pCmdLine->arguments[0],"quit") == 0){
        freeCmdLines(pCmdLine);
		_exit(EXIT_SUCCESS);
      }
      
        pid = fork();

        if (pid == 0){
          
            if(pCmdLine->inputRedirect){
            /* close(input);*/
                fd_input = open(pCmdLine->inputRedirect ,  0|64 , 0777);

                if(fd_input < 0){
                    perror("Error");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_input , 0);	
                close(fd_input);
            }
            
            
            if(pCmdLine->outputRedirect){
            /* close(output);*/
                fd_output = open(pCmdLine->outputRedirect , O_WRONLY | O_CREAT , 0777);

                if(fd_output < 0){
                    perror("Error");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_output , 1);
                close(fd_output);
            }
            
                val = execvp(pCmdLine->arguments[0],pCmdLine->arguments);
                
                if(val < 0){
                    perror("Could not execute the command");
                    _exit(EXIT_FAILURE);
                } 
                
            else{
        
            if(pCmdLine->blocking){  
                    waitpid(pid, NULL, 0);waitpid(pid, NULL, 0);
            }
            }

	  /*if(debug){
	  	fprintf(stderr, "%s","PID: ");
		fprintf(stderr, "%d\n",pid);
		fprintf(stderr, "%s","Executing command: ");
		fprintf(stderr, "%s\n",pCmdLine->arguments[0]);
	  }*/
        
        }

    }

}




int main(int argc, char const *argv[]) {
    
	int debug = 0;
	int i;
    int pipes_counter;
    pid_t pid1;

  	for (i = 1; i < argc; i++){
      
  		if (strncmp("-d", argv[i], 2) == 0)
			debug = 1;

	}
	
	
    char buf[BUFFER_SIZE];

	  while(1){
		    printCWD();
		    fgets(buf,BUFFER_SIZE,stdin);
		    cmdLine* line = parseCmdLines(buf);
            cmdLine* cmd = line;
            pipes_counter = count_pipes(cmd);
            
            if(pipes_counter == 0)
                execute(line, debug);
            
            else{
                
            int** pipes = createPipes(pipes_counter);
            int* left_pipe = NULL;
            int* right_pipe;
                    
             while (line != NULL){
                 
                  left_pipe = leftPipe(pipes, line);
                  right_pipe = rightPipe(pipes, line);
                  pid1 = fork();
                  
				if(pid1 == 0){
                 
                            if(left_pipe != NULL){ 
                                close(left_pipe[1]);
                                dup2(left_pipe[0] , 0);	
                                close(left_pipe[0]);					
                            }
                            
                            if(right_pipe != NULL){ 
                                close(right_pipe[0]);
                                dup2(right_pipe[1] , 1);	
                                close(right_pipe[1]);					
                            }
                            
                            execute(line , debug);
                            exit(0);
                    }
                        
                        else{
                            
                            if(left_pipe != NULL){
                                close(left_pipe[0]);
                                close(left_pipe[1]);
                            }	
                        }
                        
                        line = line->next;
                        
                    }
                    
                    close(left_pipe[0]);
                    close(left_pipe[1]);
                    releasePipes(pipes , pipes_counter);
                 
             }
            
		    freeCmdLines(cmd);
		    fprintf(stdout, "%c",'\n');
	  }

  return 0;
  
}
