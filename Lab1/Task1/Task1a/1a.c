#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {

    FILE* file = fopen("file.txt", "r");
    int c = fgetc(file);
    while (c != EOF){
    if ((c >= 'A') & (c <= 'Z')){
    printf("%c", '.');
}
    else{
        printf("%c", c);
    }
c = fgetc(file);
}
	fclose(file);
	 return 0;

}
