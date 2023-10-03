#ifndef REVERSI_H
#define REVERSI_H

/* maximum size of board */
#define MAX_BOARD_SIZE 16


/* identifiers for state of square in board */
#define EMPTY_SPACE 0 /* unoccupied square */
#define PLAYER1     1 /* square occupied by player 1 (O) */
#define PLAYER2     2 /* square occupied by player 2 (*) */

/* identifying whether player is human or computer */
#define HUMAN    1
#define COMPUTER 2

/* board on which the game is played, defined as a two-dimensional array
 * of squares
 */
extern int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

/* actual size of board, less than or equal to MAX_BOARD_SIZE, set to default
 * size
 */
extern int size;

/* player types */
extern int player1;
extern int player2;

/* current scores of each player */
extern int player1_score;
extern int player2_score;

/* function declarations for part 1 */
void Initialise_Board(void);
void Print_Board(void);

/* function declarations for part 2 */
int Get_Human_Move(int player, int *x, int *y);
int Get_Score(int player, int x, int y);
int Move(int player, int x, int y);

/* function declarations for part 3 */
int Best_Move(int player, int *xposition, int *yposition);

#endif /* #ifndef REVERSI_H */

