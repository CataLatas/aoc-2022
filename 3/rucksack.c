#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256

#define FALSE 0
#define TRUE  1

int map_to_priority(int item) {
    if (item >= 'a' && item <= 'z') {
        return item - 'a' + 1;
    } else {
        return item - 'A' + 27;
    }
}

int main() {
    char line[BUF_SIZE];
    char compartment_1[BUF_SIZE / 2];
    char compartment_2[BUF_SIZE / 2];
    unsigned long priority_sum = 0;
    int length;
    int i, j;
    int found;
    FILE *fin;

    fin = fopen("input.txt", "r");
    if (!fin) {
        perror("Erro ao abrir \"input.txt\"");
        return 1;
    }

    while (fgets(line, BUF_SIZE, fin)) {
        length = strlen(line) - 1;
        if (length > 0) {
            if (line[length] == '\n') {
                line[length] = '\0'; // Get rid of fgets trailing '\n'
            }

            // Apparently strncpy is derpy. Don't use it
            strcpy(compartment_1, line);
            compartment_1[length/2] = '\0';
            strcpy(compartment_2, line + length/2);

            found = FALSE;
            for (i = 0; i < length / 2 && !found; i++) {
                for (j = 0; j < length / 2 && !found; j++) {
                    if (compartment_1[i] == compartment_2[j]) {
                        priority_sum += map_to_priority(compartment_1[i]);
                        found = TRUE;
                    }
                }
            }
        }
    }

    printf("Sum of priorities: %lu\n", priority_sum);

    fclose(fin);

    return 0;
}
