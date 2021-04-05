/*
Maksim Semchuk
CS 491 - Introduction to Security
Vigenere Ciphers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  //isalpha

#include "CS491-HW-1-Program-Function-defs.h"

//Constants to be used
const int BUFFER_SIZE = 4096;
const char* FILE_NAME = "test_plaintext.txt";
const int MAX_SIZE_KEY = 4;

int main(int argc, char *argv[]){

    char selected_key[MAX_SIZE_KEY];
    size_t key_length = 0;

    if(argc == 2){
        strcpy(selected_key, argv[1]);
        key_length = strlen(selected_key);
        if(key_length >= 1 && key_length <= 4){
            printf("\nKey Accepted\n");
        }
        else{
            printf("\nThe key has to be 1-4 characters\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("\nYou need to have a argument for a string in the command line.\n");
        exit(EXIT_FAILURE);
    }

    //File IO
    char* source = NULL;
    FILE* fp = fopen(FILE_NAME, "r");
    if(fp != NULL){
        if (fseek(fp, 0L, SEEK_END) == 0) {
            /* Get the size of the file. */
            long bufsize = ftell(fp);
            if (bufsize == -1){
                printf("\nBuffer overflow\n");
                exit(EXIT_FAILURE);
            }

            /* Allocate our buffer to that size. */
            source = malloc(sizeof(char) * (bufsize + 1));

            /* Go back to the start of the file. */
            if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading file", stderr);
            } else {
                source[newLen++] = '\0'; /* Just to be safe. */
            }
        }
        fclose(fp);
    }

    //The length of the source of plaintext.txt
    int length = strlen(source);

    //Per the assignment requirements:
    //This will generate the char array for each encryption
    //for storing the encrypted message via two keys
    char encrypted_message_command_line[length];

    //to hold the generated strings
    char encryption_key_command_line[length];

    int i, j;
    //This is for command line arguments
    for(i = 0, j = 0; i < length; i++, j++){
        if(j == key_length){
            j = 0;
        }
        encryption_key_command_line[i] = selected_key[j];
    }
    encryption_key_command_line[length] = '\0';





    //Now to encrypt the message for command line:
    for(i = 0; i < length; i++){
        encrypted_message_command_line[i] = (( (source[i] + encryption_key_command_line[i]) % 26) + 'a');
    }

    //Counting the characters:

    //setting up the variables
    int count_characters_source[26] = {0};
    int count_characters_command_line[26] = {0};


    //Now to get the character count of plain text
    char c;
    for( int i = 0; i < length; i++){
        c = source[i];
        count_characters_source[(int)(tolower(c) - 'a')]++;
    }
    for( int i = 0; i < length; i++){
        c = encrypted_message_command_line[i];
        count_characters_command_line[(int)(tolower(c) - 'a')]++;
    }

    printf("\nString:\n%s", source);
    printf("\nLength of plaintext message: %ld\n\n", strlen(source) );
    /*
    printf("\n%-8s %-16s %-16s %-16s %25s\n", "Letter", "Relative Frequency", "Occurence", "Relative Frequency yz", "Relative Frequency wxyz");
    for (int i = 0; i < 26; i++) {
        printf("%-8c%10d%20.2f%%%10d%20.2f%%\n", i + 'a', count_characters[i], ( (double)count_characters[i] / length )*100 , encrypted_message[i], ((double)count_encrypted_characters[i]/length) * 100);
    }
    */
    printf("%-5s %30s %20s %30s %20s\n", "Letter", "Plaintext Count", "Plaintext Frequency", "Encrypted Count", "Encrypted Frequency");
    for (int i = 0; i < 26; i++) {
        printf("%-5c %30d %20.2f%% %30d %20.2f%%\n", i + 'a', count_characters_source[i], ( (double)count_characters_source[i]/length)*100, count_characters_command_line[i], ( (double)count_characters_command_line[i]/length)*100);
    }

    if(source){
        free(source);
    }
    exit(0);
}
