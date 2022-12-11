#include <stdlib.h>
#include <stdio.h>

#include "../include/helpers.h"

int check_overlap(int lower1, int upper1, int lower2, int upper2) {
    return (lower1 >= lower2 && upper1 <= upper2) ||
           (lower2 >= lower1 && upper2 <= upper1);
}

int check_overlap_2(int lower1, int upper1, int lower2, int upper2) {
    return !(upper1 < lower2 || upper2 < lower1);
}

int part1(FILE *file) {
    int overlap_count = 0;

    int lower1, upper1;
    int lower2, upper2;
    while (fscanf(file, "%d-%d,%d-%d", &lower1, &upper1, &lower2, &upper2) == 4) {
        if (check_overlap(lower1, upper1, lower2, upper2)) {
            //printf("OVERLAP! %d-%d,%d-%d\n", lower1, upper1, lower2, upper2);
            overlap_count++;
        }
    }

    return overlap_count;
}

int part2(FILE *file) {
    int overlap_count = 0;
    int lower1, upper1;
    int lower2, upper2;
    while (fscanf(file, "%d-%d,%d-%d", &lower1, &upper1, &lower2, &upper2) == 4) {
        if (check_overlap_2(lower1, upper1, lower2, upper2)) {
            printf("OVERLAP! %d-%d,%d-%d\n", lower1, upper1, lower2, upper2);
            overlap_count++;
        }
    }

    return overlap_count;
}

int main() {
    FILE *fin;
    int result;

    assert_example(part1, 2);
    assert_example(part2, 4);

    fin = safe_fopen("input.txt");
    result = part1(fin);
    printf("%d assingment pairs fully overlap.\n", result);

    fseek(fin, SEEK_SET, 0);
    result = part2(fin);
    printf("%d assigments pairs overlap at least partially\n", result);

    fclose(fin);

    return 0;
}
