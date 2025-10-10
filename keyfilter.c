#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ADRESS_LENGTH 128       //Max length of adress(query) string
#define MAX_ENABLED 128             //Max count of enabled characters
#define ADRESS_START 1              //The index of first argument representig the adress (how many main args to skip)
#define ASCII_SHIFT -32             //How much to shift in ascii from lower-case to upper-case

//find_match return status codes:
#define PREFIX_MATCH 10
#define MATCH 11
#define NO_MATCH 12

//Creates one adress string from argv and stores it in query
int create_adress_query(int argc, char **argv, char *query);

//Replaces lower-case with upper-case letters in string
void capitalize(char *string);

//Writes stdin line to provided string
//Stops at '\n' and replaces it with '\0'
int getline(char *string, int max_len);

//Compares query with string and returns status code:
//PREFIX_MATCH, MATCH or NO_MATCH theese need to be defined.
//If query is a prefix of adress, adds next character to next ordered string.
int find_match(char *query, char *adress, char *next);

//Writes character to a ordered string in a way that it stays ordered after.
int add_ordered(char c, char *list, int length);

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Not enough arguments!\n");
        return EXIT_FAILURE;
    }
    char query[MAX_ADRESS_LENGTH];
    char enabled[MAX_ENABLED] = "";
    int match_count = 0;
    bool found_match = false;
    char best_match[MAX_ADRESS_LENGTH];
    char adress[MAX_ADRESS_LENGTH];

    if(!(create_adress_query(argc, argv, query) == EXIT_SUCCESS)) {
        fprintf(stderr, "Create adress query failed!\n");
        return EXIT_FAILURE;
    }
    capitalize(query);

    while(getline(adress, MAX_ADRESS_LENGTH) == EXIT_SUCCESS) {
        capitalize(adress);
        int status = find_match(query, adress, enabled);
        if(status != EXIT_FAILURE) {
            if(status == MATCH) {
                strcpy(best_match, adress);
                found_match = true;
                match_count++;
            } if(status == PREFIX_MATCH) {
                if(match_count == 0) {
                    strcpy(best_match, adress);
                }
                match_count++;
            }
        } else {
            fprintf(stderr, "find_match returned Error value: %d\n", status);
            return EXIT_FAILURE;
        }
    }

    if(match_count < 0) {
        fprintf(stderr, "Invalid match_count: %d Should be at least 0\n", match_count);
        return EXIT_FAILURE;
    } else {
        if(match_count == 0) {
            printf("Not found\n");
        } else {
            if(found_match || match_count == 1) {
                printf("Found: %s\n", best_match);
            } if(match_count > 1) {
                printf("Enable: %s\n", enabled);
            }
        }
    }

    return EXIT_SUCCESS;
}

int create_adress_query(int argc, char **p_argv, char *p_query) {
    int query_idx = 0;
    for(int i = ADRESS_START; i < argc; i++) {
        for(int j = 0; p_argv[i][j] != '\0'; j++) {
            if(query_idx == MAX_ADRESS_LENGTH - 1) {
                fprintf(stderr, "Max adress length of %d exceeded in params\n", MAX_ADRESS_LENGTH);
                return EXIT_FAILURE;
            }
            p_query[query_idx] = p_argv[i][j];
            query_idx++;
        }
    }
    p_query[query_idx] = '\0';
    return EXIT_SUCCESS;
}

void capitalize(char *string) {
    for(int i = 0; string[i] != '\0'; i++) {
        if('a' <= string[i] && string[i] <= 'z') {
            string[i] += ASCII_SHIFT;
        }
    }
}

int getline(char *string, int max_len) {
    char c = 1;
    int i = 0;
    while(((c = getchar()) != '\n') && i < max_len) {
        if(c == EOF) {
            if(i == 0) {
                string[i] = c;
                return EOF;
            } else {
                string[i] = '\0';
                return EXIT_SUCCESS;
            }
        }
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    return EXIT_SUCCESS;
}

int find_match(char *query, char *adress, char *next){
    int i = 0;
    while(adress[i] != '\0') {
        if(query[i] == '\0') {
            add_ordered(adress[i], next, MAX_ADRESS_LENGTH);
            return PREFIX_MATCH;
        }
        if(adress[i] != query[i]) {
            return NO_MATCH;
        }
        i++;
    }
    if(query[i] == '\0') {
        return MATCH;
    }
    return EXIT_FAILURE;
}

int add_ordered(char c, char *string, int length) {
    for(int i = 0; i < (length - 1); i++) {
        if(string[i] == '\0') {
            string[i] = c;
            string[i+1] = '\0';
            return EXIT_SUCCESS;
        } if(c == string[i]) {
            return EXIT_SUCCESS;
        } if(c < string[i]) {
            char tmp = string[i];
            string[i] = c;
            c = tmp;
        }
    }
    fprintf(stderr, "string in add_ordered is too long");
    return EXIT_FAILURE;
}
