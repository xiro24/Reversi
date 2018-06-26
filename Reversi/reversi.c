#include "reversi.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
void initgame();
void readRestOfLine();
void initFirstPlayer();
void initSecondPlayer();
Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH]);


int main()
{
    char input[INPUT];
    bool tri =true;
    Player first;
    Player second;
	/*the while loop that runs the menu,if the user doesn't input orrectly it 
	will continously ask for the user's input*/
    while (tri){
	printf("Welcome to Reversi!  \n");
    printf("===================\n");
    printf("Select an option: \n 1. Play the Game \n 2. Quit the program\n");
    printf("please enter your choice:");
	
        fgets(input,sizeof (input),stdin);
	  
         if (strncmp(input,"2\n",sizeof(input))==0){
			printf("Goodbye. \n\n");
			tri= false;
			break;
        }
        if (strncmp(input,"1\n",sizeof(input))==0){
			tri=false;
			
			playGame(&first,&second);
			/*once the playGame(); function has completed running, the following
			if statements below will calculate the final score and declare the winner*/
			
			if (second.score >first.score){
				printf("player %s won with a whopping %d points!\n",second.name, second.score);
				main();
			} else if (second.score <first.score){
				printf("player %s won with a whopping %d points!\n",first.name, first.score);
				main();
			} else {
				printf("The game is a draw!\n");
				main();
			}
			
			
		} else {
		printf("Error Wrong Input, Please insert either a 1 or 2\n");
		
		}
	
    }

	return EXIT_SUCCESS;
}
