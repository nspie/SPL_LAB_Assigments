#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {

	int number = 0;
	int c;
	int k;
	char curr;
	int i;
	bool plus = false;
	bool minus = false;
	bool debug = false;
	bool inFile = false;
	int plusIndex = -1;
	int minusIndex = -1;
	int counter = 0;
	FILE* file = stdin;


	for(int j = 0; j < argc; j = j + 1){

	if(strncmp(argv[j], "-i", 2) == 0){
		inFile = true;
		file = fopen(argv[j] + 2, "r");
	}
	else if(strncmp(argv[j], "-D", 2) == 0){
		debug = true;
	}

	else if(strncmp(argv[j], "+e", 2) == 0){
		plus = true;
		plusIndex = j;
		
	}

	else if(strncmp(argv[j], "-e", 2) == 0){
		minus = true;
		minusIndex = j;
		
	}
	
	

	}//end for
	

	if((debug == false) & (minus == false) & (plus == false)){//no mode

	   c = fgetc(file);

	    while (c != EOF){

	    if ((c >= 'A') & (c <= 'Z')){
	    printf("%c", c + 32);
	}
	    else{
		printf("%c", c);
	    }
	   c = fgetc(file);
		
	  }
		return 0;


	}//end no mode


		

	if(debug){//debug


	   c = fgetc(file);

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
		   	c = fgetc(file);
			

		}//while /n	

		fprintf(stdout, "%c", '\n');
		fprintf(stderr, "%s", "the number of letters:");
		fprintf(stderr, "%d", counter); 
		fprintf(stdout, "%c", '\n');

		c = fgetc(file);


		}//while EOF
		
		return 0;


	}//end debug

	if(plus | minus){//e mode
		if(plus)
			k = plusIndex;
		else
			k = minusIndex;

		char digit = argv[k][2];
 
		if(digit == '1')
			number = 1;
		
		else if(digit == '2')
			number = 2;

		else if(digit == '3')
			number = 3;
		
		else if(digit == '4')
			number = 4;

		else if(digit == '5')
			number = 5;
		
		else if(digit == '6')
			number = 6;
		
		else if(digit == '7')
			number = 7;

		else if(digit == '8')
			number = 8;
		
		else if(digit == '9')
			number = 9;

		else if(digit == 'A')
			number = 10;
		
		else if(digit == 'B')
			number = 11;

		else if(digit == 'c')
			number = 12;
		
		else if(digit == 'D')
			number = 13;

		else if(digit == 'E')
			number = 14;
		
		else if(digit == 'F')
			number = 15;
		else{
			fprintf(stdout, "%s", "-ERROR-");
			fprintf(stdout, "%c", '\n');
			return 0;
		}
	}//end if e mode


	
if (minus){//minus

   c = fgetc(file);

    while (c != EOF){
	i = number;
	
	while ( c != '\n'){

		if(i <= 0)
			fprintf(stdout, "%c", c);
	   	c = fgetc(file); 
		i = i - 1;
		

	}//while /n	
	if (i > 0)
		fprintf(stdout, "%s", "-NONE-");

	
	fprintf(stdout, "%c", '\n');
	c = fgetc(file);


	}//while EOF
	return 0;

}//end minus


if(plus){//plus

   c = fgetc(file);

    while (c != EOF){
	curr = c;

	while ( c != '\n'){

		fprintf(stdout, "%c", c);
	   	c = fgetc(file);
		

	}//while /n	
	
	for(int i = 0; i < number; i = i + 1){
		fprintf(stdout, "%c", curr);
	}
	fprintf(stdout, "%c", '\n');
	c = fgetc(file);


	}//while EOF

}//end plus
	
	if (inFile)
		fclose(file);


	 return 0;

}

