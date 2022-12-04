#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 512
#define TOP_COUNT 3

int compare_lu(const void *a, const void *b) {
    unsigned long a_lu = *(unsigned long*)a;
    unsigned long b_lu = *(unsigned long*)b;

    if (a_lu < b_lu) return -1;
    if (a_lu > b_lu) return 1;
    return 0;
}

int main() {
    char line[BUF_SIZE];
    unsigned long calories = 0;
    unsigned long top_calories[TOP_COUNT] = {0};
    unsigned long calories_sum = 0;
    int i;
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
            for (i = 0; i < TOP_COUNT; i++) {
                if (calories > top_calories[i]) {
                    top_calories[i] = calories;
                    break;
                }
            }

            qsort(top_calories, TOP_COUNT, sizeof(*top_calories), compare_lu);
            calories = 0;
        }
    }

    for (i = 0; i < TOP_COUNT; i++) {
        calories_sum += top_calories[i];
    }

    printf("Sum of top 3 calories: %lu\n", calories_sum);

    fclose(fin);

    return 0;
}
