#include "reversi.h"
#include "string.h"
#include "stdio.h"

int Get_Human_Move(int player, int *x, int *y) {
    while (1) {
        char line[50];
        fgets(line, 50, stdin);
        if (line[0] == 'p') {
            return 0;
        }
        if (line[0] == 'q') {
            return -1;
        }
        sscanf(line, "%d %d", x, y);
        *x = *x - 1;
        *y = *y - 1;

        if (*x < 0 || *x >= size || *y < 0 || *y >= size) {
            continue;
        }
        if (Get_Score(player, *x, *y) <= 1) {
            fprintf(stderr, "[printed to stderr] invalid position\n");
            *x = -1;
            *y = -1;
            continue;
        }
        break;
    }
    return Get_Score(player, *x, *y);
}

int get_score_move(int player, int x, int y, int move) {
    if (x < 0 || x >= size || y < 0 || y >= size) {
        return 0;
    }
    int opponent = player == PLAYER1 ? PLAYER2 : PLAYER1;
    int total = 0;

    if (move) {
        board[y][x] = player;
    }
    /* First choosing the scan direction! */
    int yDir;
    for (yDir=-1; yDir <= 1; ++yDir) {
        int xDir;
        for (xDir=-1; xDir <= 1; ++xDir) {
            if (xDir==0 && yDir==0) {
                continue;
            }
            int lineScore=0;
            int valid = 0;
            /* Now number of steps */
            int i;
            for (i = 1; i < size; ++i) {
                int yPos=y+yDir*i;
                int xPos=x+xDir*i;
                if (yPos<0 || yPos>=size || xPos<0 || xPos>=size) {
                    break;
                }
                if (board[yPos][xPos] == opponent) {
                    lineScore++;
                }
                if (board[yPos][xPos] == player) {
                    if (i > 1) {
                        valid = 1;
                        break;
                    } else {
                        valid = 0;
                        break;
                    }
                }
                if (board[yPos][xPos] == EMPTY_SPACE) {
                    valid=0;
                    break;
                }
            }
            if (valid) {
                total += lineScore;
                if (move) {
                    int i;
                    for (i = 1; i < size; ++i) {
                        int yPos=y+yDir*i;
                        int xPos=x+xDir*i;
                        if (yPos<0 || yPos>=size || xPos<0 || xPos>=size) {
                            break;
                        }
                        if (board[yPos][xPos] == opponent) {
                            board[yPos][xPos] = player;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
    if (total == 0) {
        return 0;
    } else {
        return total+1;
    }
}

int Get_Score(int player, int x, int y) {
    return get_score_move(player, x, y, 0);
}
int Move(int player, int x, int y) {
    int score = get_score_move(player,x,y,1);
    if (player == PLAYER1) {
        player1_score += score;
        player2_score -= (score-1);
    } else {
        player2_score += score;
        player1_score -= (score-1);
    }
    return score;
}


