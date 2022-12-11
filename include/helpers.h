// (Santa's) helpers library

#include <stdio.h>

#define BUF_SIZE 1024 // May be overwritten

#define TRUE  1
#define FALSE 0

// fopen with error checking. If the file can't be opened, it exits the program with an error
FILE* safe_fopen(char const *filename);

// Reads a line from the file and strips the leading newline character
// Returns the length of the line+1 (the +1 is from before removing the newline)
int read_line(FILE *file, char* const line);

// Test the solution against the example input (assumes the existance of "exampleinput.txt")
// Exits the program entirely if failed
void assert_example(int (*solver)(FILE*), int expected);
