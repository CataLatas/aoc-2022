#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/helpers.h"

#define STACK_SIZE 256

typedef struct {
    char data[STACK_SIZE];
    int sp;
} Stack;

char stack_pop(Stack *stack) {
    if (stack->sp < 0) {
        fprintf(stderr, "Stack underflow!?\n");
        exit(1);
    }

    return stack->data[stack->sp--];
}

void stack_push(Stack *stack, char value) {
    if (stack->sp >= STACK_SIZE-1) {
        fprintf(stderr, "Stack overflow!?\n");
        exit(1);
    }

    stack->data[++stack->sp] = value;
}

void reverse_stack(Stack *stack) {
    int i;
    int tmp;
    int length = stack->sp;

    for (i = 0; i <= length / 2; i++) {
        tmp = stack->data[i];
        stack->data[i] = stack->data[length - i];
        stack->data[length - i] = tmp;
    }
}

void read_crate_line(char *line, Stack *stacks, int stack_count) {
    int i;

    // "[X] "
    for (i = 0; i < stack_count; i++) {
        line++; // Skip '['
        if (*line != ' ') {
            stack_push(&stacks[i], *line);
        }
        line += 3; // Skip "X] "
    }
}

Stack* read_crates(FILE *file, int *stack_count) {
    Stack *stacks;
    char line[BUF_SIZE];
    int i;

    read_line(file, line);

    // Get amount of stacks
    // Each line has the configuration "[C]{SPACE}[C]{SPACE}...[C]\n"
    // Each crate occupies 4 characters
    // read_line strips the "\n" at the end, so we add +1 to the strlen
    *stack_count = (strlen(line)+1) / 4;
    stacks = malloc(*stack_count * sizeof(Stack));

    for (i = 0; i < *stack_count; i++) {
        stacks[i].sp = -1;
    }

    // Read crate lines
    do {
        read_crate_line(line, stacks, *stack_count);
    } while (read_line(file, line) && line[0] != ' ');

    // The file was read top-to-bottom, the stack needs to be reversed
    for (i = 0; i < *stack_count; i++) {
        reverse_stack(&stacks[i]);
    }

    // Consume the empty line that comes after the crates
    read_line(file, line);

    return stacks;
}

void mover_9000(int count, Stack *from, Stack *to) {
    while (count-- > 0) {
        stack_push(to, stack_pop(from));
    }
}

void mover_9001(int count, Stack *from, Stack *to) {
    int i;
    char *crates = malloc(count * sizeof(char));

    for (i = 0; i < count; i++) {
        crates[i] = stack_pop(from);
    }

    while (count-- > 0) {
        stack_push(to, crates[count]);
    }

    free(crates);
}

void handle_movements(FILE *file, Stack *stacks, void (*mover)(int, Stack*, Stack*)) {
    int count, from_index, to_index;
    Stack *stack_from, *stack_to;

    while (fscanf(file, "move %d from %d to %d ", &count, &from_index, &to_index) == 3) {
        stack_from = &stacks[from_index-1];
        stack_to = &stacks[to_index-1];

        // printf("move %d from %d to %d\n", count, from_index, to_index);
        mover(count, stack_from, stack_to);
    }
}

char* get_result(Stack *stacks, int stack_count) {
    int i;
    char *result = malloc(stack_count + 1);

    for (i = 0; i < stack_count; i++) {
        result[i] = stack_pop(&stacks[i]);
    }
    result[stack_count] = '\0';

    return result;
}

char* part1(FILE *file) {
    Stack *stacks;
    char *result;
    int stack_count;

    stacks = read_crates(file, &stack_count);
    handle_movements(file, stacks, mover_9000);
    result = get_result(stacks, stack_count);

    free(stacks);
    return result;
}

char* part2(FILE *file) {
    Stack *stacks;
    char *result;
    int stack_count;

    stacks = read_crates(file, &stack_count);
    handle_movements(file, stacks, mover_9001);
    result = get_result(stacks, stack_count);

    free(stacks);
    return result;
}

int main() {
    FILE *fin;
    char *result;

    assert_example_str(part1, "CMZ");
    assert_example_str(part2, "MCD");

    fin = safe_fopen("input.txt");
    result = part1(fin);
    printf("Crate arrangement: %s\n", result);
    free(result);

    fseek(fin, SEEK_SET, 0);
    result = part2(fin);
    printf("Crate arrangement: %s\n", result);
    free(result);

    fclose(fin);

    return 0;
}

