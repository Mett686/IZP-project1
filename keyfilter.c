#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ADRESS_LENGTH 128       //Max length of our adress row
#define MAX_ENABLED 128             //Max lenght of list of enabled characters
#define ADRESS_START 1              //The index of first argument representig the adress (how many main args to skip)
#define ASCII_a 97                  //ASCII value of 'A'
#define ASCII_z 122                 //ACII value of 'Z'
#define LOWERCASE_SHIFT 32          //How much to shift in ascii from upper-case to lower-case
#define EXIT_MATCH 2                //Return value of compare func
#define EXIT_NO_MATCH 3             //Return value of compare func
#define EXIT_EOF 4                  //Return value on file end

char to_capital(char c) {
    int ascii = (int)c;
    if((ASCII_a <= ascii) && (ascii <= ASCII_z)) {
        ascii -= LOWERCASE_SHIFT;
    }
    return (char)ascii;
}

int str_copy(char *in, char *out) {
    int idx = 0;
    while(in[idx] != '\0') {
        out[idx] = in[idx];
        idx++;
    }
    out[idx] = '\0';
    return EXIT_SUCCESS;
}

int list_expand(int max_length, char character, char *list) {
    int find = (int)character;
    for(int i = 0; i < max_length; i++) {
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
        query[query_idx] = to_capital(param[char_idx]);
        query_idx++;
    }
    *p_query_idx = query_idx;
    return EXIT_SUCCESS;
}

int create_query_str(int *p_query_len, char *query, int arr_len, char **str_array) {
    int query_idx = 0;

    for(int arr_idx = ADRESS_START; arr_idx < arr_len; arr_idx++) {
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

int getline(char *p_adress) {
    char line[MAX_ADRESS_LENGTH];
    char c;
    int i = 0;
    while((c = (char)getchar()) != '\n') {
        if(c == EOF) {
            if(i == 0) {
                line[i] = EOF;
                return EXIT_EOF;
            } else {
                line[i] = '\0';
                return EXIT_SUCCESS;
            }
        }
        line[i] = to_capital(c);
        i++;
    }
    line[i] = '\0';
    str_copy(line, p_adress);
    return EXIT_SUCCESS;
}

int compare(int query_len, char *query, char *adress, char *match, char *enabled_list) {    
    for(int i = 0; i < query_len; i++) {
        if(query[i] != '\0') {
            if(query[i] != adress[i]) {
                return EXIT_NO_MATCH;
            }
        } else {
            if(adress[i] == '\0') {
                str_copy(adress, match);
                return EXIT_MATCH;
            } else {
                list_expand(MAX_ENABLED, adress[i], enabled_list);
                return EXIT_SUCCESS;
            }
        }
    }
    return EXIT_FAILURE;
}

int main(int argc, char **argv) {
    char query[MAX_ADRESS_LENGTH];
    int query_len;
    char match[MAX_ADRESS_LENGTH];
    char enabled[MAX_ENABLED];
    char adress[MAX_ADRESS_LENGTH] = " ";
    bool found_match = false;
    bool found_next = false;

    create_query_str(&query_len, query, argc, argv);

    while (getline(adress) == EXIT_SUCCESS) {
        int result = compare(query_len, query, adress, match, enabled);
        if(result == EXIT_MATCH) {
            found_match = true;
        } else if(result == EXIT_SUCCESS) {
            found_next = true;
        }
    }

    if(found_match) {
        printf("Found: %s\n", match);
    } if (found_next) {
        printf("Enable: %s\n", enabled);
    } if (!(found_match || found_next)) {
        printf("Not found\n");
    }
    return EXIT_SUCCESS;
}

//nefaka getline prepsat aby returnovala stav o konci