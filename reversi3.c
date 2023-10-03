#include "reversi.h"

int Best_Move(int player, int *xposition, int *yposition) {
    int max = 0;
    int i;
    for (i = 0; i < size; ++i) {
        int j;
        for (j = 0; j < size; ++j) {
            if (board[i][j] != EMPTY_SPACE) {
                continue;
            }
            int newScore = Get_Score(player, j, i);
            if (newScore > max) {
                max = newScore;
                *xposition = j;
                *yposition = i;
            }
        }
    }
    return max;
}
