#include <stdio.h>
#include <string.h>

#define BUF_SIZE 8

// Moves
#define STONE    0
#define SHEET    1
#define CLIPPERS 2

// Outcomes
#define LOSE 0
#define DRAW 1
#define WIN  2

const int OUTCOME_SCORES[] = { 0, 3, 6 };

const int PLAYER_MOVES[][3] = {
    //           PLAYER
    //  LOSE      DRAW      WIN
    { CLIPPERS, STONE,    SHEET },    // OPPONENT -> Stone
    { STONE,    SHEET,    CLIPPERS }, // OPPONENT -> Sheet
    { SHEET,    CLIPPERS, STONE }     // OPPONENT -> Clippers
};

int calculate_score(int opponent_move, int player_outcome) {
    // Map ('A' 'B' 'C') to (0 1 2)
    opponent_move -= 'A';

    // Map ('X' 'Y' 'Z') to (0 1 2)
    player_outcome -= 'X';

    return PLAYER_MOVES[opponent_move][player_outcome]+1 + OUTCOME_SCORES[player_outcome];
}

int main() {
    char line[BUF_SIZE];
    unsigned int total_score = 0;
    FILE *fin;

    fin = fopen("input.txt", "r");
    if (!fin) {
        perror("Erro ao abrir \"input.txt\"");
        return 1;
    }

    while (fgets(line, BUF_SIZE, fin)) {
        if (strcmp(line, "\n")) {
            total_score += calculate_score(line[0], line[2]); // "OPPONNENT[space]PLAYER"
        }
    }

    printf("Total score: %u\n", total_score);

    fclose(fin);

    return 0;
}
