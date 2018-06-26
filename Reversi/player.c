#include "player.h"
#include "utility.h"
#include "stdbool.h"
/**
 * These two functions initialise the player structure at the beginning of the
 * game. In both cases, you should initialise the whole structure to known safe
 * values and then prompt the user for their name. In the initFirstPlayer()
 * function you should then select a color at random for this player using the
 * rand() function. This token should be assigned to the first player's token.
 * In initSecondPlayer() you should just test the value of token and assign the
 * opposite color to the second player.
 * 
 * Note that an empty name is not valid and the user should be re-prompted.
 **/
void readRestOfLine();

void initFirstPlayer(Player * player)
{    
	bool run =true;
	
	/*the while loop will prompt the player for it's correct input
	if the player exceeds the char array limit it will throw an overflow error
	and then run the code in the while loop again.*/
	while(run ==true ){
    	printf("Please insert Player1's name: ");
	fgets(player->name, sizeof (player->name) ,stdin);
	
	if (player->name[strlen(player->name)-1]!='\n'){
	    printf("overflow\n");
	    readRestOfLine();
	} else if (strlen(player->name)>sizeof(player->name)){
		printf("overflow\n");
	    readRestOfLine();
		run =true;
	}else {
		run = false;
	}

	player->name[strcspn(player->name,"\n")]='\0';
	}
}

void initSecondPlayer(Player * player, Cell token)
{
	
	bool run =true;
	/*Pretty much the same as the initFirstPlayer() function, instead it determines
	the token of player two which can then be used to assign the first player's
	token to the opposite token colour.*/
	while (run == true){
    	printf("Please insert Player2's name: ");
	fgets(player->name, sizeof (player->name) ,stdin);
	
	if (player->name[strlen(player->name)-1]!='\n'){
	    printf("overflow\n");
	    readRestOfLine();
	} else if (strlen(player->name)>sizeof(player->name)){
		printf("overflow\n");
	    readRestOfLine();
		run=true;
	} else {
		run =false;
	}

	player->name[strcspn(player->name,"\n")]='\0';
	}


    if (rand()%3==RED){
	player->token=RED;
    } else if (rand()%3==CYAN || rand()%3 == BLANK || rand()%3!=RED){
	player->token=CYAN;
    }
}
