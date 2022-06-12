#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
char censor(char c) {
  if(c == '!')
    return '*';
  else
    return c;
}
 
char* map(char *array, int array_length, char (*f) (char)){
    
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  
    for(int i = 0; i < array_length; i = i + 1){
        
        mapped_array[i] = (*f)(array[i]);
        
    }

  return mapped_array;
  
}


char encrypt(char c){/* Gets a char c and returns its encrypted form by adding 2 to its value.  If c is not between 0x41 and 0x7a it is returned unchanged */
    if (c < 0x41 || c > 0x7a)
        return c;
    else
        return c + 2;
    
}
        
char decrypt(char c){ /* Gets a char c and returns its decrypted form by reducing 2 to its value.  If c is not between 0x41 and 0x7a it is returned unchanged */
    if(c < 0x41 || c > 0x7a)
        return c;
    else
        return c - 2;   
    
}

char dprt(char c){ /* dprt prints the value of c in a decimal representation followed by a new line, and returns c unchanged. */
    printf("%d\n", c);
    return c;
    
}

char cprt(char c){/* If c is a number between 0x41 and 0x7a, cprt prints the character of ASCII value c followed 
                    by a new line. Otherwise, cprt prints the dot ('*') character. After printing, cprt returns 
                    the value of c unchanged. */
 
     if(c >= 0x41 && c <= 0x7a)
        printf("%c\n", c);

    else
        printf("%s\n", "*");
    
    return c;
 
 
}
char my_get(char c){ /* Ignores c, reads and returns a character from stdin using fgetc. */
    return fgetc(stdin);
    
}

char quit(char c){ /* Gets a char c,  and if the char is 'q' , ends the program with exit code 0. Otherwise returns c. */
	if (c == 'q')
		exit(0);
	else
		return c;

}



typedef struct fun_desc {
  char *name;
  char (*fun)(char);
}fun_desc;




 
int main(int argc, char **argv){
	char* carray = (char*)malloc(5 * sizeof(char));
	
	struct fun_desc menu[] = { { "censor", censor }, { "Encrypt", encrypt }, { "Decrypt", decrypt } , { "Print dec", dprt }, { "Print string", cprt },
 	{ "Get string", my_get } , {"Quit" , quit } , { NULL, NULL }};
    
    size_t length = sizeof menu / sizeof menu[0];
    
	int c = 0;
    	int x = 1;

	while (x == 1){
	
	printf("%s\n", "Please choose a function:");
	
	for(int i = 0; i < length - 1; i = i + 1){
	printf("%d%s", i, ") ");
	printf("%s\n", menu[i].name);
    }
	
    
	printf("%s", "option: ");
    c = fgetc(stdin);
    fgetc(stdin);

	
	if(c >= '0' && c < length - 1 - 48)
		printf("%s\n", "Within bounds");
	else
		return 0;
				
	
    carray = map(carray, 5, menu[c - 48].fun);
    printf("%s", "Done");
    printf("%s", "\n");
    printf("%s", "\n");


	}
    
}
