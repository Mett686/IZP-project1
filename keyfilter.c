#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
            
#define MAX_ADDRESS_LENGTH 128       // Max length of address(query) string
#define MAX_ENABLED 256             // Max count of enabled characters
#define ARG_COUNT 2                 // Number of supported args
#define ASCII_SHIFT -32             // Difference between lowercase and uppercase in ascii

// address_cmp status codes (cannot be 1):
#define PREFIX_MATCH 2
#define MATCH 3
#define NO_MATCH 4

// Replaces lowercase with uppercase letters in string
void capitalize(char *string);

// Reads stdin into provided string
// Stops at '\n' or EOF and replaces it with '\0'
int scanline(char *string, int max_len);

// Compares query with string and returns status code:
// PREFIX_MATCH, MATCH or NO_MATCH (theese need to be defined)
// If query is a prefix of address, writes it to next with add_ordered().
int address_cmp(char *query, char *address, char *next);

// Inserts character to a ordered string in a way that it stays ordered after.
int add_ordered(char c, char *list, int length);

int main(int argc, char **argv) {

    char query[MAX_ADDRESS_LENGTH] = ""; // argv
    char address[MAX_ADDRESS_LENGTH];     // stdin
    char enabled[MAX_ENABLED] = "";     // string of enabled chars
    int match_count = 0;                //
    bool match_found = false;           // has exatct match been found
    char best_match[MAX_ADDRESS_LENGTH]; // string to be printed if found

    // Check for argument compliance
    // skip strcpy() if no argument is provided
    if(argc != ARG_COUNT) {
        if(argc > ARG_COUNT) {
            fprintf(stderr, "Too many arguments. Maximum: %d\n", ARG_COUNT-1);
            return EXIT_FAILURE;
        }
    } else {
        if(strlen(argv[1]) > MAX_ADDRESS_LENGTH) {
            fprintf(stderr, "Argument 1 of main is too long. Maximum size: %d\n", MAX_ADDRESS_LENGTH);
            return EXIT_FAILURE;
        }
        strcpy(query, argv[1]);
    }
    
    capitalize(query);

    // While there is still something to read from stdin
    // compare it using address_cmp status
    // - store in best_match if MATCH or PREFIX_MATCH
    // - expand enabled with characters on PREFIX_MATCH
    // - increment match count on each match
    while(scanline(address, MAX_ADDRESS_LENGTH) == EXIT_SUCCESS) {
        capitalize(address);

        int status = address_cmp(query, address, enabled);

        if(status == EXIT_FAILURE) {
            fprintf(stderr, "address_cmp returned Error value: %d\n", status);
            return EXIT_FAILURE;
        } if(status == MATCH) {
            strcpy(best_match, address);
            match_found = true;
            match_count++;
        } else if(status == PREFIX_MATCH) {
            if(match_count == 0) {
                strcpy(best_match, address);
            }
            match_count++;
        }
    }

    // Print results dictated by match_count and match_found
    if(match_count == 0) {
        printf("Not found\n");
    } else {
        if(match_found || match_count == 1) {
            printf("Found: %s\n", best_match);
        } if(match_count > 1) {
            printf("Enable: %s\n", enabled);
        }
    }
    return EXIT_SUCCESS;
}

void capitalize(char *string) {
    for(int i = 0; string[i] != '\0'; i++) {
        if('a' <= string[i] && string[i] <= 'z') {
            string[i] += ASCII_SHIFT;
        }
    }
}

int scanline(char *string, int max_len) {
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

int address_cmp(char *query, char *address, char *next){
    int i = 0;
    while(address[i] != '\0') {
        if(query[i] == '\0') {
            add_ordered(address[i], next, MAX_ADDRESS_LENGTH);
            return PREFIX_MATCH;
        }
        if(address[i] != query[i]) {
            return NO_MATCH;
        }
        i++;
    }
    if(query[i] == '\0') {
        return MATCH;
    }
    return NO_MATCH;
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
    fprintf(stderr, "string in add_ordered is too long\n");
    return EXIT_FAILURE;
}