#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 512

int main() {
    char line[BUF_SIZE];
    unsigned long calories = 0;     // Calories accumulator
    unsigned long max_calories = 0; // Maximum number of calories an elf was found holding
    FILE *fin;

    fin = fopen("input.txt", "r");
    if (!fin) {
        perror("Erro ao abrir \"input.txt\"");
        return 1;
    }

    while (fgets(line, BUF_SIZE, fin)) {
        if (strcmp(line, "\n")) {
            calories += strtoul(line, NULL, 0);
        } else {
            if (calories > max_calories) {
                max_calories = calories;
            }

            calories = 0;
        }
    }

    printf("Maximum calories: %lu\n", max_calories);

    fclose(fin);

    return 0;
}
