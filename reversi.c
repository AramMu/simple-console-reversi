/* reversi.c: containing the main() function. DO NOT MODIFY!!!! */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "reversi.h"

/* board on which the game is played, defined as a two-dimensional array
 * of squares
 */
int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

/* actual size of board, less than or equal to MAX_BOARD_SIZE, set to default
 * size
 */
int size = 12;

/* player types, defaulting to human versus human */
int player1 = HUMAN;
int player2 = HUMAN;

/* current scores of each player, initialised to zero */
int player1_score = 0;
int player2_score = 0;

/* strpreicmp()
 * 
 * This is used to parse the command line options!
 * Check to see if str1 is a prefix of str2 
 * Case of strings is ignored
 * returns 0 if not a prefix
 * returns 1 otherwise
 */
static int strpreicmp(const char *str1, const char *str2)
{
    while (*str1 != '\0') {
	if (toupper(*str1++) != toupper(*str2++))
	    return 0;
    }
    return 1;
}

/* valid_moves()
 * 
 * checks whether there are valid moves left for any player on the board. 
 * returns nonzero if yes, zero otherwise. 
 */
int valid_moves()
{
    int chosenx, choseny;
    int score1, score2;
    score1 = Best_Move(PLAYER1, &chosenx, &choseny);
    score2 = Best_Move(PLAYER2, &chosenx, &choseny);
    return (score1 || score2);
}

/* play_turn()
 * Plays one of the turn on the board. 
 * player_side indicate which player it is the turn of, 
 * player_type indicate whether it is a computer or a human player.
 * the function returns -1 if the game is over, and the score otherwise. 
 */
int play_turn(int player_side, int player_type)
{
    int score, checkscore;
    int chosenx, choseny;

    if (player_type == HUMAN) {
	/* prompt human player 1 for their turn */
	score = Get_Human_Move(player_side, &chosenx, &choseny);

	/* check for game termination */
	if (score == -1)
	    return -1;
    } else
	/* if player 1 is the computer, check that Best_Move() is implemented */
    {
	/* get score of move for player 1that gives the biggest score */
	score = Best_Move(player_side, &chosenx, &choseny);

	if (score == -1) {	/* illegal score */
	    fprintf(stderr,
		    "Computer generated move (Best_Move()) not implemented\n");
	    exit(-1);
	}
    }

    /* check for pass */
    if (score == 0) {
	fprintf(stderr, "Player %i has passed\n", player_side);
    } else {
	/* make move on the board */
	checkscore = Move(player_side, chosenx, choseny);

	if (score != checkscore) {
	    printf("inconsistent scores %d %d for player %i move\n",
		   score, checkscore, player_side);
	    exit(-1);
	}
    }

    /* print the new state of the board */
    Print_Board();

    /* check for end game */
    if (valid_moves())
	return score;
    else
	return -1;
}

/*
 ********************************************************************
 ************************* Main Program *****************************
 ********************************************************************
 *
 *		Should not be modified by the student
 */
int main(int argc, char *argv[])
{
    int currentarg = 1;
    char *curarg;
    int score = 0;

    /* parse the command line options */
    while (currentarg < argc) {
	/* get the current argument */
	curarg = argv[currentarg];

	/* ignore the '-' */
	if (curarg[0] == '-')
	    curarg++;
	else {
	    /* print argument list and exit */
	    fprintf(stderr, "%s -size <size> -users hh/hc/ch/cc\n",
		    argv[0]);
	    exit(-1);
	}

	if (strpreicmp(curarg, "size")) {
	    /* first check there is an argument */
	    if ((currentarg + 1) == argc) {
		/* print an error message and exit */
		fprintf(stderr, "%s: Missing argument for option -size.\n",
			argv[0]);
		exit(-1);
	    }

	    /* get the argument value */
	    curarg = argv[++currentarg];
	    size = atoi(curarg);
	    if (size < 4 || size > MAX_BOARD_SIZE) {
		/* print an error message and exit */
		fprintf(stderr,
			"%s: Board size must be between 4 and %i\n",
			argv[0], MAX_BOARD_SIZE);
		exit(-1);
	    }

	    if (size % 2 != 0) {
		/* print an error message and exit */
		fprintf(stderr, "%s: Board size must be even\n", argv[0]);
		exit(-1);
	    }

	    fprintf(stderr, "The size of board has been set to %i\n",
		    size);
	} else if (strpreicmp(curarg, "users")) {
	    /* check there is an argument */
	    if ((currentarg + 1) == argc) {
		/* print an error message and exit */
		fprintf(stderr, "%s: Missing argument for option -users\n",
			argv[0]);
		exit(-1);
	    }

	    /* get the argument */
	    curarg = argv[++currentarg];
	    if (curarg[0] == 'h')
		player1 = HUMAN;
	    else if (curarg[0] == 'c')
		player1 = COMPUTER;
	    else {
		/* print an error message and exit */
		fprintf(stderr,
			"%s: Illegal argument \"%s\" for option -users.\n",
			argv[0], curarg);
		exit(-1);
	    }

	    if (curarg[1] == 'h')
		player2 = HUMAN;
	    else if (curarg[1] == 'c')
		player2 = COMPUTER;
	    else {
		/* print an error message and exit */
		fprintf(stderr,
			"%s: Illegal argument \"%s\" for option -users.\n",
			argv[0], curarg);
		exit(-1);
	    }

	    /* valid oppenents selected */
	    fprintf(stderr, "The users have been selected as %s vs. %s\n",
		    (player1 == HUMAN) ? "human" : "computer",
		    (player2 == HUMAN) ? "human" : "computer");
	} else {
	    /* print argument list and exit */
	    fprintf(stderr, "%s -size <size> -users hh/hc/ch/cc\n",
		    argv[0]);
	    exit(-1);
	}

	/* next argument */
	currentarg++;
    }

    /* initialise board to starting position and print starting position */
    Initialise_Board();
    Print_Board();

    /* start game */
    for (;;) {
	/* first player */
	score = play_turn(PLAYER1, player1);

	/* end game ? */
	if (score == -1)
	    break;

	/* second player */
	score = play_turn(PLAYER2, player2);

	/* end game ? */
	if (score == -1)
	    break;
    }

    /* game is over */
    printf("Game over\n");
    return 0;
}
