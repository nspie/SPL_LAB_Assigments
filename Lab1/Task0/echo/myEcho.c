#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {

    char word[256];
    fgets(word, sizeof(word), stdin);
    printf(word);
    return 0;

}
