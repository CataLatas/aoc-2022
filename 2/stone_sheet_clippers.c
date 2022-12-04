#include <stdio.h>
#include <string.h>

#define BUF_SIZE 8

// Moves
#define STONE    0
#define SHEET    1
#define CLIPPERS 2

// Outcome scores
#define LOSE 0
#define DRAW 3
#define WIN  6

const int OUTCOMES[][3] = {
    //     PLAYER
    // ST    SH    CL
    { DRAW, WIN,  LOSE }, // OPPONENT -> Stone
    { LOSE, DRAW, WIN },  // OPPONENT -> Sheet
    { WIN,  LOSE, DRAW }  // OPPONENT -> Clippers
};

int calculate_score(int opponent_move, int player_move) {
    int score;

    // Map ('A' 'B' 'C') to (0 1 2)
    opponent_move -= 'A';

    // Map ('X' 'Y' 'Z') to (0 1 2)
    player_move -= 'X';

    if (opponent_move == player_move) {
        score = DRAW + player_move+1;
    } else {
        score = OUTCOMES[opponent_move][player_move] + player_move+1;
    }

    return score;
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
