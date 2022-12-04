#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256

#define GROUP_SIZE 3

#define FALSE 0
#define TRUE  1

int preprocess_line(char* const line) {
    int length = strlen(line);
    if (length > 0 && line[length] == '\n') {
        line[length] = '\0';
    }

    return length;
}

int read_group(char* const rucksacks, int lengths[GROUP_SIZE], FILE* const fin) {
    int i;
    int success = TRUE;
    char line[BUF_SIZE];

    rucksacks[0] = '\0';
    for (i = 0; i < GROUP_SIZE && success; i++) {
        if (fgets(line, BUF_SIZE, fin) && preprocess_line(line) > 0) {
            strcat(rucksacks, line);
            lengths[i] = strlen(line);
        } else {
            success = FALSE;
        }
    }

    return success;
}

int map_to_priority(int item) {
    if (item >= 'a' && item <= 'z') {
        return item - 'a' + 1;
    } else {
        return item - 'A' + 27;
    }
}

int main() {
    char rucksacks[BUF_SIZE * GROUP_SIZE];
    int lengths[GROUP_SIZE];
    unsigned long priority_sum = 0;
    int i, j, k; // Horrible but works
    int found;
    FILE *fin;

    fin = fopen("input.txt", "r");
    if (!fin) {
        perror("Erro ao abrir \"input.txt\"");
        return 1;
    }

    while (read_group(rucksacks, lengths, fin)) {
        found = FALSE;
        // lord forgive me for this atrocity
        // TODO: Fix this up. what the fuck is this shit
        for (i = 0; i < lengths[0] && !found; i++) {
            for (j = lengths[0]; j < lengths[0]+lengths[1] && !found; j++) {
                for (k = lengths[0]+lengths[1]; k < lengths[0]+lengths[1]+lengths[2] && !found; k++) {
                    if (rucksacks[i] == rucksacks[j] && rucksacks[i] == rucksacks[k]) {
                        priority_sum += map_to_priority(rucksacks[i]);
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
