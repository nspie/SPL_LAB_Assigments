#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {

	int number = 0;
	int c;
	char curr;
	int i;
	bool plus = false;
	bool debug = false;
	int counter = 0;



	if(argc == 1){//no arguments

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
	return 0;


}//end no arguments

	else {//argc > 1
		if((strncmp ("+e", argv[1], 2) == 0))
			plus = true;
		else if(strncmp ("-D", argv[1], 2) == 0)
			debug = true;

		

if(debug){//debug


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
	
	return 0;


}//end debug

		char digit = argv[1][2];
 
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


	
if (plus == false){//minus

   c = fgetc(stdin);

    while (c != EOF){
	i = number;
	
	while ( c != '\n'){

		if(i <= 0)
			fprintf(stdout, "%c", c);
	   	c = fgetc(stdin); 
		i = i - 1;
		

	}//while /n	
	if (i > 0)
		fprintf(stdout, "%s", "-NONE-");

	
	fprintf(stdout, "%c", '\n');
	c = fgetc(stdin);


	}//while EOF
	return 0;

}//end minus


if(plus){//plus

   c = fgetc(stdin);

    while (c != EOF){
	curr = c;

	while ( c != '\n'){

		fprintf(stdout, "%c", c);
	   	c = fgetc(stdin);
		

	}//while /n	
	
	for(int i = 0; i < number; i = i + 1){
		fprintf(stdout, "%c", curr);
	}
	fprintf(stdout, "%c", '\n');
	c = fgetc(stdin);


	}//while EOF

}//end plus

}//end elif

	 return 0;

}

