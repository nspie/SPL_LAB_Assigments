#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {

	bool debug = false;
	if ((argc > 1) && (strncmp ("-D", argv[1], 2) == 0)){
	debug = true;
	}
int c;
int counter = 0;

	
if (debug == false){

   c = fgetc(stdin);

    while (c != EOF){

    if ((c >= 'A') & (c <= 'Z')){
    printf("%c", '.');
}
    else{
        printf("%c", c);
    }
   c = fgetc(stdin);
	
  }
}


else{
	
   c = fgetc(stdin);

    while (c != EOF){
	counter = 0;
	while ( c != '\n'){

	    if ((c >= 'A') & (c <= 'Z')){ 
	    	fprintf(stdout, "%c", '.');
		fprintf(stderr, "%d", c);
		fprintf(stderr, "%s", " ");
		fprintf(stderr, "%d", 46);
		fprintf(stderr, "%s", " ");
		counter = counter + 1;
	}
	    else{
	    	fprintf(stdout, "%c", c);
		fprintf(stderr, "%d", c);
		fprintf(stderr, "%s", " ");
		fprintf(stderr, "%d", c);
		fprintf(stderr, "%s", " ");

	    }
		fprintf(stderr, "%c", '\n');
	   	c = fgetc(stdin);
		

	}//while /n	

	fprintf(stdout, "%c", '\n');
	fprintf(stderr, "%s", "the number of letters:");
	fprintf(stderr, "%d", counter); 
	fprintf(stdout, "%c", '\n');

	c = fgetc(stdin);


	}//while EOF

}//else

	 return 0;

}

