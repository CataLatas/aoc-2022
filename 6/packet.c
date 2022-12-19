#include <stdio.h>
#include <stdlib.h>

#include "../include/helpers.h"

#define NOT_FOUND -1

int part1(FILE *file) {
    char line[BUF_SIZE];
    int length;
    int i;
    int result = NOT_FOUND;

    length = read_line(file, line) + 1;
    puts(line);

    for (i = 0; i < length-4 && result == NOT_FOUND; i++) {
        // The fuck... Will need to be changed for part2
        if (!(line[i+0] == line[i+1] || line[i+0] == line[i+2] || line[i+0] == line[i+3] || line[i+1] == line[i+2] || line[i+1] == line[i+3] || line[i+2] == line[i+3])) {
            result = i + 4;
        }
    }

    if (result == -1) {
        fprintf(stderr, "Okay wtf.\n");
        exit(1);
    }

    return result;
}

int part2(FILE *file) {
    return 666; // Not implemented
}

int main() {
    FILE *fin;
    int result;

    assert_example(part1, 7);
    assert_example(part2, 19);

    fin = safe_fopen("input.txt");
    result = part1(fin);
    printf("First start-of-packet: %d\n", result);

    fseek(fin, SEEK_SET, 0);
    result = part2(fin);
    printf("First start-of-packet: %d\n", result);

    fclose(fin);

    return 0;
}

