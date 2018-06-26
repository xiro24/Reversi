#include "gameboard.h"
#include <stdio.h>
#include <string.h>
/**
 * Initialise the game board to be consistent with the screenshot provided
 * in your assignment specification. 
 *
 * All squares should be initialised to be blank other than the four
 * squares in the middle of the board. In that case they are initialised to 
 * appropriate colored tokens.
 **/

void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int i=0;
	int j=0;
	/*pretty much what the assignment spec tells you to do
	assign all of the ceels to blank and set only the 4 to their respective
	colours*/
		for (i=0;i<8;i++){
		for (j=0;j<8;j++){
			board[i][j] = BLANK;
	    }	
		}
	
	board[3][4]=CYAN;
	board[4][3]=CYAN;
	board[3][3]=RED;
	board[4][4]=RED;

}

/*i**
 * Display the board as specified in the assignment specification. You should 
 * make every effort to create a board consistent with the screenshots in the 
 * assignment specification.
 **/
void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * first, Player * second)
{
	int i;
	int j;
	
	/*this prints the start of the gameboard prints the interface of the score
	and status*/
	if(second->token==RED){
	first->token=CYAN;
        printf("======================================================================\n");
        printf("Player One's Details:\n--------------------\n");
        printf("Name: %s\tScore: %i\tToken Colour: %s0%s\n",first->name,first->score,
		COLOR_CYAN,COLOR_RESET);

        printf("----------------------------------------------------------------------\n");
        printf("Player Two's Details:\n--------------------\n");
        printf("Name: %s\tScore: %i\tToken Colour: %s0%s\n",second->name,second->score,
		COLOR_RED,COLOR_RESET);
    } else  if(second->token==CYAN) {
	first->token=RED;
        printf("======================================================================\n");
        printf("Player One's Details:\n--------------------\n");
        printf("Name: %s\tScore: %i\tToken Colour: %s0%s\n",first->name,first->score,
		COLOR_RED,COLOR_RESET);

        printf("----------------------------------------------------------------------\n");
        printf("Player Two's Details:\n--------------------\n");
        printf("Name: %s\tScore: %i\tToken Colour: %s0%s\n",second->name,second->score,
		COLOR_CYAN,COLOR_RESET);	

    } else {
	first->token=CYAN;
        printf("======================================================================\n");
        printf("Player One's Details:\n--------------------\n");
        printf("Name: %s\tScore: %i\tToken Colour: %s0%s\n",first->name,first->score,
		COLOR_CYAN,COLOR_RESET);

	second->token=RED;
        printf("----------------------------------------------------------------------\n");
        printf("Player Two's Details:\n--------------------\n");
        printf("Name: %s\tScore: %i\tToken Colour: %s0%s\n",second->name,second->score,
		COLOR_RED,COLOR_RESET);

    }

    printf("----------------------------------------------------------------------\n");
	/*this prints the gameboard and the tokens according to the value of the cells in 
	board[x][y];*/
    printf("     1   2   3   4   5   6   7   8\n");
    printf("====================================\n");
    for (i=0;i<BOARD_HEIGHT;i++){
	printf(" %d ",i+1);
	for (j= 0; j<BOARD_WIDTH;j++){
	printf("%s|",COLOR_RESET);
	
	if ((board[i][j]==RED)){
		printf("%s O ",COLOR_RED);
      } else if((board[i][j]==CYAN)) {
			printf("%s O ",COLOR_CYAN);
	 	   } else {
			board[i][j]=BLANK;
			printf("   ");
		    }
	    if (j==BOUNDARY){
		printf("%s|",COLOR_RESET);
	    }
	}
	printf("\n");
	if (i<BOUNDARY){ 
	    printf("------------------------------------\n");
	} else {
	    printf("====================================\n\n");
	}
	}
   
}
