#include <stdio.h>
#include <stdlib.h>

#define MAX_ADRESS_LENGTH 128 //Max length of our adress row
#define ADRESS_START 1 //The index of first argument representig the adress
#define A 65 //ASCII value of 'A'
#define Z 90 //ACII value of 'Z'
#define LOWERCASE_SHIFT 32 //How much to shift in ascii from upper-case to lower-case

char to_lower(char c) {
    int ascii = (int)c;
    if ((A <= ascii) && (ascii <= Z)) {
        ascii += LOWERCASE_SHIFT;
    }
    return (char)ascii;
}



int main(int argc, char **argv) {
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("Arg%d: %s\n", i, argv[i]);
    }

    #if 1
    char adresa[MAX_ADRESS_LENGTH] = {};

    scanf("%s\n", adresa);
    printf("%s\n", adresa);
    #endif


    #if 1
    for (int i = ADRESS_START; i < argc; i++) {
        printf("%c  ", to_lower(argv[i][0]));
    }
    #endif


    #if 0
    char adress_str[MAX_ADRESS_LENGTH] = {};
  
    for (int word_idx = ADRESS_START; word_idx < argc; ++word_idx) {
        for (int char_idx = 0; argv[word_idx][char_idx] != ' '; ++char_idx) {

        }
    }
    #endif



    return 0;
}