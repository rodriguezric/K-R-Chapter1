#include <stdio.h>
#define MAXLINE   1000
#define TABWIDTH     4
/**
 * Title:   Line Library
 * Author:  Ricardo Rodriguez
 * Summary: A small library for handling lines.
 *
 * Description:
 * Lines in the context of this library are strings
 * that are terminated with two characters: \n \0
 * I built this library for solving the K&R chap1
 * exercises. The code convention is:
 *
 * Functions:
 *  noun_verb
 *
 * Mutations:
 *  (target[, source][, limit])
 **/

/**
 * Reads from stdin and stores to line. 
 **/
int line_read(char target[], int limit);

/* Reverses the characters in a line up
 * until it reaches \n */
void line_reverse(char target[]);

/* Copies the line from source to target */
void line_copy(char target[], char source[]);

/* Returns the number of characters 
 * before reaching \n */
int line_size(char line[]);

/* Returns the last index of the line 
 * before reaching \n */
int line_last_index(char line[]);

/* Returns the number of characters 
 * including \n and \0. This is to 
 * be used with line_copy */
int line_limit(char line[]);

/**
 * Replaces \t with TABWIDTH spaces. 
 **/
void line_detab(char target[]);

/**
 * replaces TABWIDTH spaces with \t.
 **/
void line_entab(char target[]);


int main()
{
    char line[MAXLINE];

    while ((line_read(line, MAXLINE)) != 0) {
        line_entab(line);
        printf("%s", line);
    }
}

int line_read(char target[], int limit) 
{
    char c;
    int i = 0;

    while((c = getchar()) != EOF && c != '\n') {
        target[i] = c;
        i++;
    }

    if (c == '\n') {
        target[i] = c;
        i++;
    }

    target[i] = '\0';

    return i;
}

void line_reverse(char target[])
{
    int last_index = line_last_index(target);
    int limit = line_limit(target);
    char copy[limit];

    line_copy(copy, target);
    
    for(int i = 0; i <= last_index; i++) {
        target[i] = copy[last_index - i];
    }
}

void line_copy(char target[], char source[])
{
    int i = 0;
    int limit = line_limit(source);
    
    while (i < limit - 1 && source[i] != '\0') {
        target[i] = source[i];
        i++;
    }

    target[i] = '\0';
}

int line_size(char line[])
{
    int i = 0;

    while(line[i] != '\n')
        i++;

    return i;
}

int line_last_index(char line[])
{
    return line_size(line) - 1;
}

int line_limit(char line[])
{
    return line_size(line) + 2;
}

void line_detab(char target[])
{
    int limit = line_limit(target);
    char modified[MAXLINE];
    int offset = 0;
    
    for(int i = 0; i <= limit; i++) {
        if (target[i] == '\t') {
            for(int j = 0; j < TABWIDTH; j++) 
                modified[i + j + offset] = ' ';

            offset += (TABWIDTH - 1);
        }
        else
            modified[i + offset] = target[i];
    }

    line_copy(target, modified);
}

void line_entab(char target[])
{
    int limit = line_limit(target);
    char modified[MAXLINE];
    int offset = 0;
    int count = 0;

    for (int i = 0; i <= limit; i++) {
        if (target[i] == ' ') {
            count++;
        }

        if (count == TABWIDTH) {
            offset += (TABWIDTH - 1);
            count = 0;
            
            modified[i - offset] = '\t';
        }
        else 
            modified[i - offset] = target[i];
    }

    line_copy(target, modified);
}

