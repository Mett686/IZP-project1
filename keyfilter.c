#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ADRESS_LENGTH 128       //Max length of our adress row
#define MAX_FOUND 128               //Max lenght of list of found characters
#define ADRESS_START 1              //The index of first argument representig the adress (how many main args to skip)
#define ASCII_a 97                  //ASCII value of 'A'
#define ASCII_z 122                 //ACII value of 'Z'
#define LOWERCASE_SHIFT 32          //How much to shift in ascii from upper-case to lower-case
#define MATCH 2                     //Return value of compare func
#define NO_MATCH 3                  //Return value of compare func

char to_capital(char c) {
    int ascii = (int)c;
    if((ASCII_a <= ascii) && (ascii <= ASCII_z)) {
        ascii -= LOWERCASE_SHIFT;
    }
    return (char)ascii;
}

int str_copy(int len, char *in, char *out) {
    for(int i = 0; i < len; i++) {
        out[i] = in[i];
    }
    return EXIT_SUCCESS;
}

int list_expand(int max_length, char character, char *list) {
    int find = (int)character;
    for(int i = 0; i < max_length; i++) {
        printf("Idx: %d\n", i);
        printf("Searched char: %c\n", (char)find);
        if(list[i] == (int)'\0') {
            list[i] = find;
            list[i + 1] = '\0';
            return EXIT_SUCCESS;
        }
        if(find <= (int)list[i]) {
            if(find == (int)list[i]) {
                return EXIT_SUCCESS;
            }
            char write = (char)find;
            find = (int)list[i];
            list[i] = write;
        }
    }
    return EXIT_FAILURE;
}

int param_parser(int *p_query_idx, char *query, char *param) {
    int query_idx = *p_query_idx;
    
    for(int char_idx = 0; param[char_idx] != '\0'; char_idx++) {
        if(query_idx >= MAX_ADRESS_LENGTH - 1) {
            query[query_idx] = '\0';
            fprintf(stderr, "Query string exceeded max length of %d", MAX_ADRESS_LENGTH);
            return EXIT_FAILURE;
        }
        //printf("    char idx: %d    char: %c\n", char_idx, to_lower(param[char_idx])); //debug
        query[query_idx] = to_capital(param[char_idx]);
        query_idx++;
    }
    *p_query_idx = query_idx;
    //printf("query: %s\n", query); //debug
    return EXIT_SUCCESS;
}

int create_query_str(int *p_query_len, char *query, int arr_len, char **str_array) {
    int query_idx = 0;

    for(int arr_idx = ADRESS_START; arr_idx < arr_len; arr_idx++) {
        //printf("Array idx: %d\nQuery idx: %d\nParam: %s\n", arr_idx, query_idx, str_array[arr_idx]); //debug
        if(param_parser(&query_idx, query, str_array[arr_idx]) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        } if(arr_idx != arr_len-1) {
            query[query_idx] = ' ';
            query_idx++;
        }
    }
    *p_query_len = query_idx + 1;
    query[query_idx] = '\0';
    return EXIT_SUCCESS;
}

char *getline() {
    static char line[MAX_ADRESS_LENGTH];
    char c;
    int i = 0;
    while((c = (char)getchar()) != '\n') {
        //printf("char - %c\n", c); //debug
        if(c == EOF) {
            if(i == 0) {
                line[i] = EOF;
                return line;
            }
            line[i] = '\0';
            return line;
        }
        line[i] = to_capital(c);
        i++;
    }
    line[i] = '\0';
    printf("Adress: %s\n", line); //debug
    printf("Adress len: %d\n", i + 1); //debug
    return line;
}

int compare(int query_len, char *query, char *adress, char *match, char *enabled_list) {    
    for(int i = 0; i < query_len; i++) {
        if(query[i] != '\0') {
            if(query[i] != adress[i]) {
                return NO_MATCH;
            }
        } else {
            if(adress[i] == '\0') {
                str_copy(query_len, adress, match);
                return MATCH;
            } else {
                list_expand(MAX_FOUND, adress[i], enabled_list);
                return EXIT_SUCCESS;
            }
        }
    }
    return EXIT_FAILURE;
}

int main(int argc, char **argv) {
    #if 1 //debug
    printf("argc: %d\n", argc);
    for(int i = 0; i < argc; i++) {
        printf("arg%d: %s\n", i, argv[i]);
    }
    #endif
    
    //char query[MAX_ADRESS_LENGTH];
    //int query_len = 0;
    
    //create_query_str(&query_len, query, argc, argv);
    //printf("Query: %s\n", query);
    //printf("Query len: %d\n", query_len);

    char idk[MAX_FOUND] = "ABDZ";
    list_expand(MAX_FOUND, 'F', idk);
    list_expand(MAX_FOUND, 'D', idk);
    list_expand(MAX_FOUND, 'C', idk);
    list_expand(MAX_FOUND, 'G', idk);
    list_expand(MAX_FOUND, '%', idk);
    printf("\nList: %s\n", idk);

    //getline();

    return EXIT_SUCCESS;
}