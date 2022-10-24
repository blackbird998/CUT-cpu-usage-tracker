#include <stdio.h>
#include "threads/reader.c"

int main(void){
    printf("Hi\n");

    struct Stats stat;
    readFile(&stat);


    
    return 0;
}