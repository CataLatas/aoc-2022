#include <stdio.h>
#include <stdlib.h>

#include "../include/helpers.h"

#define NOT_FOUND -1

int find_start_of_packet(char const *line, int length, int packet_size) {
    int i, j, k;
    int found = FALSE;
    int result;

    // Horrible? Not sure
    for (i = 0; i < length-packet_size && !found; i++) {
        result = i + packet_size;
        found = TRUE;

        for (j = 0; j < packet_size && found; j++) {
            for (k = j+1; k < packet_size && found; k++) {
                found = (j != k && line[i+j] != line[i+k]);
            }
        }
    }

    if (!found) {
        return NOT_FOUND;
    }

    return result;
}

int part1(FILE *file) {
    char line[BUF_SIZE];
    int length;
    int result;

    length = read_line(file, line) + 1;
    puts(line);

    result = find_start_of_packet(line, length, 4);

    if (result == NOT_FOUND) {
        fprintf(stderr, "Okay wtf.\n");
        exit(1);
    }

    return result;
}

int part2(FILE *file) {
    char line[BUF_SIZE];
    int length;
    int result;

    length = read_line(file, line) + 1;
    puts(line);

    result = find_start_of_packet(line, length, 14);

    if (result == NOT_FOUND) {
        fprintf(stderr, "Okay wtf.\n");
        exit(1);
    }

    return result;
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

