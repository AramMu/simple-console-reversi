#include "reversi.h"
#include <stdio.h>

void Initialise_Board(void){
    int i;
    for (i = 0; i < size; ++i) {
        int j;
        for (j = 0; j < size; ++j) {
            board[i][j] = EMPTY_SPACE;
        }
    }
    board[size/2][size/2-1] = PLAYER1;
    board[size/2-1][size/2] = PLAYER1;
    board[size/2-1][size/2-1] = PLAYER2;
    board[size/2][size/2] = PLAYER2;
    player1_score = player2_score = 2;

}
void Print_Board(void){
    printf("\n");
    printf("   ");
    int i;
    for (i = 0; i < size; ++i) {
        printf("%2d", i+1);
    }
    printf("\n    ");
    for (i = 0; i < size; ++i) {
        printf("_ ");
    }
    printf("\n");
    for (i = 0; i < size; ++i) {
        printf("%2d: ", i+1);
        int j;
        for (j = 0; j < size; ++j) {
            switch(board[i][j]) {
            case EMPTY_SPACE:
                printf(". ");
                break;
            case PLAYER1:
                printf("O ");
                break;
            case PLAYER2:
                printf("* ");
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("Player 1 (O) score: %d\n", player1_score);
    printf("Player 2 (*) score: %d\n", player2_score);
}
