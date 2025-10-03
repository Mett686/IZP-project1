#include <stdio.h>
#include <stdlib.h>

#define MAX_ADRESS_LENGTH 128 //Max length of our adress row
#define ADRESS_START 1 //The index of first argument representig the adress
#define A 65 //ASCII value of 'A'
#define Z 90 //ACII value of 'Z'
#define LOWERCASE_SHIFT 32 //How much to shift in ascii from upper-case to lower-case

char to_lower (char c) {
    int ascii = (int)c;
    if ((A <= ascii) && (ascii <= Z)) {
        ascii += LOWERCASE_SHIFT;
    }
    return (char)ascii;
}

int str_copy (char *str, char *destination) {
    for (int i = 0; str[i] != '\0'; i++) {
        destination[i] = str[i];
        if (i >= MAX_ADRESS_LENGTH - 1) {
            destination[i] = '\0';
            return -1;
        }
    }
    return 0;
}

int create_adress (char *adress, int arr_len, char **p_str_array) {
    int adress_idx = 0;

    for (int arr_idx = ADRESS_START; arr_idx < arr_len; arr_idx++) {
        for (int char_idx = 0; p_str_array[arr_idx][char_idx] != '\0'; char_idx++) {
            adress[adress_idx] = to_lower(p_str_array[arr_idx][char_idx]);
            adress_idx++;

            if (adress_idx >= MAX_ADRESS_LENGTH - 1) {
            adress[adress_idx] = '\0';
            return -1;
            }
        }
        if (arr_idx != arr_len-1) {
            adress[adress_idx] = ' ';
            adress_idx++;
        }
    }
    adress[adress_idx] = '\0';
    return 0;
}


int main(int argc, char **argv) {
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("Arg%d: %s\n", i, argv[i]);
    }
    char adress[MAX_ADRESS_LENGTH];

    create_adress(adress, argc, argv);
    printf("%s\n", adress);
    
    return 0;
}