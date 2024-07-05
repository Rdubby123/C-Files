// Ryan DuBrueler & Shreyas Harish

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "llist.h"

#define MAX_LINE_LENGTH 200
#define MAX_WORD_LENGTH 200 // not given, set to max line length
#define MAX_WORDS 10000

// Structure to hold a word along with its line numbers
struct WordReference {
    char word[MAX_WORD_LENGTH];
    llist lineNumbers; // Linked list to store line numbers
};

// Function prototypes
static int parseLine(char *line, struct WordReference wordTable[], int *uniqueWordCount, int lineNumber);
static void addWordToList(char *word, struct WordReference wordTable[], int *uniqueWordCount, int lineNumber);
static void printTable(struct WordReference wordTable[], int uniqueWordCount);
static void printOutput(struct WordReference wordTable[], int uniqueWordCount, int lineNumber, int allWordCount);

static int compareWordReferences(const void* a, const void* b) {
    return strcmp(((struct WordReference*)a)->word, ((struct WordReference*)b)->word);
}

int main(int argc, char **argv) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    struct WordReference wordTable[MAX_WORDS];
    int uniqueWordCount = 0, allWordCount=0, lineNumber = 1; // Lines start at 1
    
    fp = fopen(argv[1], "r"); // opens the input file
    
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    // Reads each line from the file
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        
        // parseLine tokenizes all of the words in a line, puts them into the 
        // wordTable, and returns the number of words in each line
        allWordCount+=parseLine(line, wordTable, &uniqueWordCount, lineNumber);
        lineNumber++; // Increments line number each time line is read
    }

    fclose(fp);
    qsort(wordTable, uniqueWordCount, sizeof(struct WordReference), compareWordReferences);

    // Print all output, lineNumber-1 from initializer
    printOutput(wordTable, uniqueWordCount,lineNumber-1,allWordCount);

    return 0;
}

// Function to print all output
static void printOutput(struct WordReference wordTable[], int uniqueWordCount, int lineNumber, int allWordCount) {
    printf("Proj. #4 - Ryan DuBrueler & Shreyas Harish\n\n");
    printTable(wordTable,uniqueWordCount);
    printf("\nTotal unique words: %d\n",uniqueWordCount);
    printf("Total words: %d\n",allWordCount);
    printf("Total lines: %d",lineNumber);

}

// prints each word along with its unique line numbers
static void printTable(struct WordReference wordTable[], int uniqueWordCount) {
    printf("Word\t\tReferences\n");
    printf("--------------- -------------\n");
    
    for (int i = 0; i < uniqueWordCount; i++) {
        printf("%-16s", wordTable[i].word);
        
        // number of lines
        int size = listSize(wordTable[i].lineNumbers);
        
        // print the first line number
        if (size > 0) {
            printf("%d", getItem(wordTable[i].lineNumbers, 0));
            int prevLineNumber = getItem(wordTable[i].lineNumbers, 0);
            
            // print the next line numbers, if any
            for (int j = 1; j < size; j++) {
                int currentLineNumber = getItem(wordTable[i].lineNumbers, j);
                if (currentLineNumber != prevLineNumber) {
                    printf(", %d", currentLineNumber);
                    prevLineNumber = currentLineNumber;
                }
            }
        }
        printf("\n");
    }
}

// Function to parse a line into individual words and store their line numbers in the wordTable
static int parseLine(char *line, struct WordReference wordTable[], int *uniqueWordCount, int lineNumber) {
    char *token, cleanToken[MAX_WORD_LENGTH];
    int lineWordCount = 0; // Initializes count

    // Gets the first token
    token = strtok(line, " \n!@#$%^&*()-_+={[]}|\\\"':;<,>.?~`"); 
    
    // Iterates through other tokens
    while (token != NULL) {
        // Makes a token free of non-letters to add to the table
        int cleanIndex = 0;
        for (int i = 0; token[i] != '\0'; i++) {
            if ((token[i] >= 'a' && token[i] <= 'z') || ((token[i] >= 'A') && (token[i] <= 'Z'))) {
                cleanToken[cleanIndex++] = token[i];
            }
        }
        cleanToken[cleanIndex] = '\0'; // clean token null byte

        // Adds the cleaned token to the word table if it's not empty
        if (cleanIndex > 0) {
            addWordToList(cleanToken, wordTable, uniqueWordCount, lineNumber);
            lineWordCount++; // Increments word count
        }

        // Gets the next token
        token = strtok(NULL, " \n!@#$%^&*()-_+={[]}|\\\"':;<,>.?~`");
    }

    return lineWordCount; // Returns the word count
}


// Function to add a word to the wordTable
static void addWordToList(char *word, struct WordReference wordTable[], int *uniqueWordCount, int lineNumber) {
    bool wordExists = false; // Assumes not in table for now
    // Checks if the word is already in the wordTable
    for (int i = 0; i < *uniqueWordCount; i++) {
        if (strcmp(wordTable[i].word, word) == 0) {
            // existing linenumber + current linenumber, if statement may be unneccesary
            if(addItem(&(wordTable[i].lineNumbers), lineNumber)){ 
                wordExists = true;
                break;
            }
        }
    }
    // if the word is not in the wordTable, adds it
    if (!wordExists) {
        strcpy(wordTable[*uniqueWordCount].word, word); // copies word to table 
        addItem(&(wordTable[*uniqueWordCount].lineNumbers), lineNumber); 
        // adds linenumber to existing linenumbers
        (*uniqueWordCount)++; // Increments unique word count after adding a word
    }
}





