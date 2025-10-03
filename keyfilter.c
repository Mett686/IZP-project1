#include <stdio.h>
#include <stdlib.h>

#define MAX_ADRESS_LENGTH 128   //Max length of our adress row
#define ADRESS_START 1          //The index of first argument representig the adress
#define A 65                    //ASCII value of 'A'
#define Z 90                    //ACII value of 'Z'
#define LOWERCASE_SHIFT 32      //How much to shift in ascii from upper-case to lower-case

char to_lower(char c) {
    int ascii = (int)c;
    if((A <= ascii) && (ascii <= Z)) {
        ascii += LOWERCASE_SHIFT;
    }
    return (char)ascii;
}

int create_query_str(char *query, int arr_len, char **str_array) {
    int query_idx = 0;

    for(int arr_idx = ADRESS_START; arr_idx < arr_len; arr_idx++) {
        for(int char_idx = 0; str_array[arr_idx][char_idx] != '\0'; char_idx++) {
            query[query_idx] = to_lower(str_array[arr_idx][char_idx]);
            query_idx++;

            if(query_idx >= MAX_ADRESS_LENGTH - 1) {
            query[query_idx] = '\0';
            return -1;
            }
        }
        if(arr_idx != arr_len-1) {
            query[query_idx] = ' ';
            query_idx++;
        }
    }
    query[query_idx] = '\0';
    return 0;
}

//char *read_stdin(char *query, char **matching_adr) {
//    char *adress[MAX_ADRESS_LENGTH];
//    int getline(adress);
//    for(int i = 0; i < MAX_ADRESS_LENGTH - 1; i++) {
//
//    }
//}

int main(int argc, char **argv) {
    char query[MAX_ADRESS_LENGTH];
    create_query_str(query, argc, argv);
    
    for( int i = 0; i < 5; i++) {
        char negr[25] ;
        getline(stdin, negr,'\n');
        printf("%s\n", negr);
    }







    printf("%s\n", query); //debug



    return 0;
}