#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <stdbool.h>




typedef struct virus {

    unsigned short sigSize;

    unsigned char* sig;

    char virusName[16];

} virus;





typedef struct link link;

struct link {

    link *nextVirus;

    virus *vir;

};




void printHex(unsigned char buffer[], int length, FILE* output){

    unsigned char ch;

    int i = 0;



    while(i < length){

        ch = buffer[i];

        fprintf(output, "%02X ", ch);

        i++;

    }

    fprintf(output, "%c", '\n');

}



void linkDead(link* link){

    if(link != NULL){

        //free(link->nextVirus);

        //free(link->vir->sig);


    }

}



int fpeek(FILE *stream){

    int c;



    c = fgetc(stream);

    ungetc(c, stream);



    return c;

}







void readVirus(virus* vir, FILE* input){ /* this function receives a pointer to a virus struct and a file pointer and

overwrites the given virus struct so that it represents the next virus in the file.

To read from a file, use fread(). See man fread(3) for assistance.*/



    char buff[2];



    size_t read =  fread(buff, 1, 2, input);//0-2 signatureLength

    if(read == 0)

        return;



    short number = (buff[1] << 8) + buff[0];



    vir->sigSize = number;

    vir->sig = (unsigned char*)(malloc(number));



    fread(vir->sig, 1 , vir->sigSize, input);//2-N signature



    fread(vir->virusName, 1, 16, input);//2+N - 16 name



}





void printVirus(virus* vir, FILE* output){ /* this function receives a virus and a pointer to an output file. The function

prints the virus to the given output. It prints the virus name (in ASCII), the virus signature length (in decimal), and the virus signature

(in hexadecimal representation).*/





    fprintf(output, "virus name: %s\n", vir->virusName);

    fprintf(output, "virus size: %d\n", vir->sigSize);

    fprintf(output, "%s\n", "signature");

    printHex(vir->sig, vir->sigSize, output);





}





void list_print(link *virus_list, FILE* output){/* Print the data of every link in list to the given stream. Each item followed by a newline character. */

    link* curr = virus_list;


    if( curr->nextVirus != NULL){
        do{

            printVirus(curr->vir, output);

            curr = curr->nextVirus;

            printf("%c", '\n');

        } while(curr->nextVirus != NULL);
    }

}





link* list_append(link* virus_list, link* to_add){  /* Add the given link to the list

 (either at the end or the beginning, depending on what your TA tells you),

 and return a pointer to the list (i.e., the first link in the list).

 If the list is null - return the given entry. */



    if(virus_list == NULL)

        return to_add;



    //add to beginning

    to_add->nextVirus = virus_list;

    return to_add;



}



void list_free(link *virus_list){ /* Free the memory allocated by the list. */

    linkDead(virus_list);

}





void detect_virus(char *buffer, unsigned int size, link *virus_list){

    link* curr = virus_list;


    while(curr->nextVirus != NULL){

        for(int i = 0; i < size - curr->vir->sigSize; i++){

            int compare = memcmp(buffer, curr->vir->sig, curr->vir->sigSize);

            if(compare == 0){

                printf("%p", &(buffer[i]));

                printf("%s", curr->vir->virusName);

                printf("%d", curr->vir->sigSize);

            }



        }

        curr = curr->nextVirus;



    }

}



void quit(){



    exit(0);



}


link* loadSignatures(link* virus_list){


    char input[256];
    scanf("%s", input);
    fgetc(stdin);

    FILE* file = fopen(input, "r");


    if(file != NULL){

        //read viruses into virusList.

        while(fpeek(file) != EOF){


            virus* virus1 = (virus*) malloc(sizeof(virus));

            readVirus(virus1, file);

            link *virus_link1 = (link*)malloc(sizeof(link));

            virus_link1->vir = virus1;

            virus_list = list_append(virus_list, virus_link1);
        }
        return virus_list;
        fclose(file);
        //return 1;
    }

    else{
        return NULL;
    }

}



int main(int argc, char **argv){

    link *virus_list = (link*)malloc(sizeof(link));
    int loadedFile = 0;



    //FILE* file = fopen(argv[1], "r");



    int c;

    while (1){

        printf("1) Load signatures\n");

        printf("2) Print signatures\n");

        printf("3) Detect viruses\n");

        printf("4) Quit\n");

        printf("Please choose a function:\n");



        c = fgetc(stdin);
        printf("%c prev c", c);

        fgetc(stdin);

        printf("%s", "\n");
        printf("%d this is ccccc", c);



        //Load

        if(c == '1'){

            printf("%s\n", "Enter a signature file name: ");
            printf("%s", "entered c==1");


            //loadedFile =
            virus_list = loadSignatures(virus_list);
        }

        else if (c == '2' && virus_list != NULL){
            fprintf(stderr, "%s", "entered c==2");
            list_print(virus_list, stdout);


        }
            //Detect

        else if (c == '3'){

            printf("%s", "entered c==3");

            char buff[10000];

            char fileName[256];

            scanf("%s", fileName);
            fgetc(stdin);


            FILE *file = fopen(fileName, "r");

            int readBytes = fread(buff,1, 10000, file);

            detect_virus(buff, readBytes, virus_list);

        }


            //Quit

        else if (c == '4'){

            printf("%s\n", "Exiting\n");

            quit();

        }



            //un-Identified command

        else{

            printf("%s\n", "Out of bounds\n");

            quit();


        }
    }
    return 0;

}
