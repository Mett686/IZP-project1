#include <stdio.h>
#include <stdlib.h>

//idk whats happening
//help me

int main(int argc, char *argv[]) {
    printf("argc: %d\n", argc);
    
    for (int i = 0, i < argc, ++i) {
        printf("%c ", argv[i]);
    }
    printf("Hello world!");

    return 0;
}