#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

FILE* safe_fopen(char const *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Could not open \"%s\": %s\n", filename, strerror(errno));
        exit(1);
    }

    return f;
}

int read_line(FILE *file, char* const line) {
    int length = 0;

    if (fgets(line, BUF_SIZE, file)) {
        length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[--length] = '\0';
        }
    }

    return length;
}

void assert_example(int (*solver)(FILE*), int expected) {
    int result;
    FILE *example_file = safe_fopen("exampleinput.txt");

    result = solver(example_file);
    if (result != expected) {
        fprintf(stderr, "Example failed. Expected %d, but result was %d\n", expected, result);
        exit(1);
    }

    fclose(example_file);
    puts("Example passed!");
}

void assert_example_str(char* (*solver)(FILE*), char const* expected) {
    char *result;
    FILE *example_file = safe_fopen("exampleinput.txt");

    result = solver(example_file);
    if (strcmp(result, expected)) {
        fprintf(stderr, "Example failed. Expected \"%s\", but result was \"%s\"\n", expected, result);
        exit(1);
    }

    fclose(example_file);
    puts("Example passed!");

    free(result);
}

