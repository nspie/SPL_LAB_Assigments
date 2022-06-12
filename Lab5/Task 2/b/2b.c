#include "LineParser.h" 
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


#define BUFFER_SIZE 2048
#define TERMINATED  -1
#define RUNNING 1
#define SUSPENDED 0


typedef struct process{
    cmdLine* cmd;                   /* the parsed command line*/
    pid_t pid; 		                /* the process id that is running the command*/
    int status;                     /* status of the process: RUNNING/SUSPENDED/TERMINATED */
    struct process *next;	        /* next process in chain */
} process;

process* global_process_list;


char* getStatusString(int status){
    
    if(status == TERMINATED)
      return "Terminated";
    
    else if(status == RUNNING)
      return "Running";
    
    else          
      return "Suspended";
}


process *list_append(process* process_list, cmdLine* cmd, pid_t pid){
    
    if(process_list == NULL){
        process* new_process = malloc(sizeof(process));
        new_process->cmd = cmd;
        new_process->pid = pid;
        new_process->status = RUNNING;
        new_process->next = NULL;
        return new_process;
    }
    
    else
        process_list->next = list_append(process_list->next,cmd, pid);
    
    return process_list;
}


void addProcess(process** process_list, cmdLine* cmd, pid_t pid){
    
  *process_list = list_append(*process_list, cmd, pid);

}



void printProcess(process* process){
    
    char command[100]="";
    int i;
    
    if(process->cmd->argCount > 0)
        for(i = 0; i < process->cmd->argCount; i++){
        strcat(command,process->cmd->arguments[i]);
        strcat(command," ");
    }
    printf("%d\t\t%s\t%s\n", process->pid, command, getStatusString(process->status));
    
}


void list_print(process* process_list){
    process* curr_process = process_list;
    
    while(curr_process != NULL){
        printProcess(curr_process);
        curr_process = curr_process->next;
    }
}



void freeProcessList(process* process_list){
    
    process* curr_process = process_list;
    
    if(curr_process != NULL){
        
        freeProcessList(curr_process->next);
        freeCmdLines(curr_process->cmd);
        free(curr_process->cmd);
        free(curr_process);
    }
    
}


void updateProcessStatus(process* process_list, int pid, int status){
    
  int new_status = RUNNING;
  
  if(WIFEXITED(status) || WIFSIGNALED(status))
    new_status = TERMINATED;
  
  else if(WIFSTOPPED(status))
    new_status = SUSPENDED;
  
  else if(WIFCONTINUED(status))
    new_status = RUNNING;
  
  process_list->status = new_status;
  
}


void updateProcessList(process **process_list){
    
    process* curr_process = *process_list;
    
    while(curr_process != NULL){
        
        int status;
        pid_t pid = waitpid(curr_process->pid, &status, WNOHANG | WUNTRACED | WCONTINUED);
        
        if(pid != 0)   /*pid argument has changed state*/
            updateProcessStatus(curr_process, curr_process->pid ,status);
        
        curr_process=curr_process->next;
    }
}



void delete_process(process* toDelete){
    
    freeCmdLines(toDelete->cmd);
    toDelete->cmd = NULL;
    toDelete->next = NULL;
    free(toDelete);
    toDelete = NULL;
}


int deleteTerminatedProcesses(process** process_list){
    
    process* curr_process = *process_list;
    process* prev_process;
    
    /*deleting the head*/
    if(curr_process != NULL && curr_process->status == TERMINATED){
        *process_list = curr_process->next;
        delete_process(curr_process);
        return 1;
    }
    
    /*iterate to the next terminated process*/
    while (curr_process != NULL && curr_process->status != TERMINATED){
        prev_process = curr_process;
        curr_process=curr_process->next;
    }
    
    /*none terminated found*/
    if(curr_process == NULL)
        return 0;
    
    else{
        prev_process->next = curr_process->next;
        delete_process(curr_process);
        return 1;
    }
}



void printProcessList(process** process_list){

    updateProcessList(process_list);
    printf("PID\t\tCommand\t\tSTATUS\n");
    list_print(*process_list);
    while(deleteTerminatedProcesses(process_list)){};
    
}


void printCWD(){
  char path_name[PATH_MAX];
  getcwd(path_name,PATH_MAX);
  fprintf(stdout, "%s\n",path_name);
}



int specialCommand(cmdLine* command, int debug){
    
  int special = 0;
    
  if(strcmp(command->arguments[0],"cd") == 0){
      
    special = 1;
        
    int val = chdir("..");
    
    if(val < 0){
      perror("ERROR on cd command");
    
    if(debug)
        fprintf(stderr, "%s\n","ERROR on cd command");

    }
  }
  
  	else if(strcmp(command->arguments[0],"nap") == 0){
        
		special = 1;
        
	int nap_time = atoi(command->arguments[1]);	
        int nap_pid = atoi(command->arguments[2]);
        
        int suspend_fork = fork();
        int kill_status;
        
        if (suspend_fork == 0){
            kill_status = kill(nap_pid, SIGTSTP);

        
        if (kill_status == -1)
            perror("kill SIGTSTP failed");
        
        else{
            
            printf("%d handling SIGTSTP:\n",nap_pid);
            sleep(nap_time);
            kill_status = kill(nap_pid, SIGCONT);
            
          if (kill_status == -1)
            perror("kill SIGCONT failed");
          
          else
            printf("%d handling SIGCONT\n",nap_pid);
        }
                _exit(1);

        }
        
              /*  updateProcessList(global_process_list);*/

    }
        
	  

	else if(strcmp(command->arguments[0],"showprocs") == 0){
		special = 1;
		printProcessList(&global_process_list);
	  }
	  
	  
    else if(strcmp(command->arguments[0],"stop") == 0){
        
        special = 1;
        
        int stop_pid = atoi(command->arguments[1]);
        if( kill(stop_pid,SIGINT) == -1)    /*terminated*/
        perror("kill SIGINT failed");
        else
        printf("%d handling SIGINT\n",stop_pid);        
        }
        
        /*updateProcessList(global_process_list);*/
  
  
  return special;
}




void execute(cmdLine* pCmdLine, int debug){
    
    if(specialCommand(pCmdLine, debug) == 0){

  if(strcmp(pCmdLine->arguments[0],"quit") == 0)
	exit(EXIT_SUCCESS);

    pid_t pid = fork();
    int val = 0;

  if (pid == 0){ 
	val = execvp(pCmdLine->arguments[0],pCmdLine->arguments);
	}
	
  if(pid != -1)  //child success
      addProcess(&global_process_list, pCmdLine, pid);

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

  global_process_list = NULL;

  for (i = 1; i < argc; i++){
      
  	if (strcmp("-d", argv[i]) == 0)
		debug = 1;
}

  FILE* input = stdin;
  char buf[BUFFER_SIZE];

  while(1){

    printCWD();
    fgets(buf,BUFFER_SIZE,input);
    cmdLine* line = parseCmdLines(buf);
    execute(line, debug);
    fprintf(stderr, "%c",'\n');


  }

  return 0;
}
