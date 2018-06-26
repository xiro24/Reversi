#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
/**
 * The heart of the game itself. You should do ALL initialisation required
 * for the game in here or call function required for that purpose. For example
 * both players should be initialised from here, you should seed the random
 * number generator, etc...
 * 
 * Next, you should set the initial player - the initial player is the player
 * whose token was set to RED.
 * 
 * Next you will need to manage the game loop in here. In each loop of the
 * game, you should display the game board, including player scores
 * display whose turn it is, etc... in the format from the assignment
 * specification. Finally at the end of each turn you will calculate the score
 * for :wq
 * each player and store it and then you will need to swap the current player
 * and other player using the swapPlayer() function.
 * 
 * A game will end when either player presses enter on a newline.
 * 
 * When you detect a request to end the game you should do a final calculation
 * of the scores for the two players and return the player with the highest
 * score - if its a draw return NULL.
 **/
 
void readRestOfLine();

Player * playGame(Player * first, Player * second)
{
	bool change=true;
    bool run =true;
	bool points =true;
	bool runOnce=true;
    Player *fptr;
    Player *sptr;
    Player **ffptr;
    Player **ssptr;
	    
    Cell board[BOARD_HEIGHT][BOARD_WIDTH];
	srand(time(NULL));
	
    fptr = first;
    sptr = second;

    ffptr=&fptr;
    ssptr=&sptr;
	
    initBoard(board);
    initFirstPlayer(first);
    initSecondPlayer(second, second->token);
	
	/* the while loop runs the game*/
	while (run){
		/*checks if points need to be updated or not if it does then it
		turns the boolean points to false else it will use the standard score 2
		at the beginning of the game*/
		if (points){
			second->score=2;
			first->score=2;
		} else {
			second->score=gameScore(board,second->token);
			first->score=gameScore(board,first->token);
		}
		/*the displa board will continously print the board
		once all the board values have been updated*/
		displayBoard(board,first,second);
		/*this will determine which player will go first, so then the player that's
		red will always go first. I added the extra boolean variable here so then it can fall
		into a continous loop with the statements below which allow the players to swtch turns 
		included inside each turn. I've placed the makeMove() function to determine if the player
		has entered an '\n', if so it will return false which would then exit the while loop.
		i've also placed the makeMove() function to switch the pointers to the other player*/
		if (runOnce==true) {
			if (first->token==RED){
				printf("It's player %s turn\n",first->name);
				change = false;
				if (makeMove(first,board)==false) {
					run=false;
				}else {
					swapPlayers(ffptr,ssptr);
				}
			} else if (second->token==RED){
				printf("It's player %s turn\n",second->name);
				change = true;
				if (makeMove(second,board)==false) {
					run=false;
				}else {
					swapPlayers(ffptr,ssptr);
				}
			}
		}

		if (runOnce==false){
			if (first->token==RED && change==true){
				printf("It's player %s turn\n",first->name);
				change = false;
				if (makeMove(first,board)==false) {
					run=false;
				}else {
					swapPlayers(ffptr,ssptr);
				}
			} else if (second->token==RED && change==false){
				printf("It's player %s turn\n",second->name);
				change = true;
				if (makeMove(second,board)==false) {
					run=false;
				}else {
					swapPlayers(ffptr,ssptr);
				}
			}else if (second->token==CYAN && change==false){
				printf("It's player %s turn\n",second->name);
				change = true;
				if (makeMove(second,board)==false) {
					run=false;
				}else{
					swapPlayers(ffptr,ssptr);
				}
			} else if (first->token==CYAN && change==true ){
				printf("It's player %s turn\n",first->name);
				change = false;
				if (makeMove(first,board)==false) {
					run=false;
				}else {
					swapPlayers(ffptr,ssptr);
				}
			}
		}
		/*this wil only allow the if statements that aren't updatable run only once*/
		runOnce=false;
		points=false;	
	}
    return NULL;
}





/**
 * Prompts the user for a comma-separate pair of coordinates for a move in the
 * game. Each move, if valid, must capture at least one enemy piece by
 * surrounding a sequence of one or more enemy pieces with two pieces of our
 * own: one being the new piece to be placed and the other a piece already
 * on the board. This function then validates that a valid move has been entered
 * and calls the applyMove() function to do the actual work of capturing pieces.
 * 
 * FALSE is returned if an empty line is entered (to end the game), otherwise
 * the prompt will continue until a valid move is entered and then TRUE is returned.
 **/
Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
    char cords[COORDINATES];
    char *tokenizer;
    int x=0;
    int y=0;
	bool run=true;
	
	/*this while loop keeps running if the player inserts incorrect coordinates
	if the coordinates entered are too large(long) it will print an overflow message
	and ask for the input again. I've placed the applyMove() after converting the chars
	into ints (and after all of ther other validation if statements) so then i could
	utilize the return value. If it returns true then the move was achieved if
	it returns false, then the move has failed and the while loop repeats.*/
	while (run ==true){
		printf("Please enter the x and y co-ordinate seperated by a ,\n");
		fgets(cords,COORDINATES,stdin);
	
		if (cords[0]=='\n'){
			return false;
		}
		if (cords[strlen(cords)-1]!='\n'){
			if (strlen(cords)>COORDINATES){
				printf("overlfow\n");
				readRestOfLine();
			} else {
				printf("overlfow\n");
				readRestOfLine();
			}
		}
		else if (strlen(cords)==4){
			if (cords[1]!=','){
				printf("you must insert a , along with the correct ");
				printf("coordinates in the correct positions\n");
			} else if (cords[0]==','){
				printf("you must insert a , along with the correct ");
				printf("coordinates in the correct positions\n");
			} else if (cords[2]==','){
				printf("you must insert a , along with the correct ");
				printf("coordinates in the correct positions\n");
			}			
			else {
			tokenizer= strtok(cords,",");
			if (tokenizer!=NULL){
				y = strtol(cords,&tokenizer,0);
				
				tokenizer=strtok(NULL,"\n");
				
				x = strtol(tokenizer,&tokenizer,0);	

				if ((x>0 && x<9) && (y>0 && y<9)) {
					if (applyMove(board,y,x,player->token)==true){
						run=false;
						return true;
					} else {
						run=true;
					}
				}
			} else {
				printf("invalid input\n");
			}
			}
		}  else {
			printf("ERROR\n");
			run=true;
		}
	}
	return true;
}

/**
 * Applys the move requested by the user to the game board.
 * 
 * It iterates over all the directions from the coordinate specified to see
 * whether there are any pieces that can be captured.
 * 
 * If there are no pieces that can be captured in any direction it is an
 * invalid move and FALSE is returned (with no changes to the board occurring),
 * otherwise TRUE is returned, the pieces are captured and the token is
 * placed on the board.
 **/
Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token)
{	
	int xtemp=x-1;
	int ytemp=y-1;
	int xT=x-1;
	int yT=y-1;
	int activated=0;
	bool activate = false; 
	bool run =true;
	
	
	
   /*This large hile loop searches each seperate directon specifically to that direction only.
   the functions work pretty similar to each one but with only slight variation in the code.
   This first if statement clears the first hurdle of whether or not the coordinates are
   correct. I've added an "activate" if statement to check whether or not a token was
   changed or notif it has changed then the funtion will increment activated so the the
   if statement at the end can tell the function calling it if a token has been moved or not*/
	if (board[xtemp][ytemp]==BLANK){
		/*move right*/
		if (board[xT][y]!=token && board[xT][y]!=BLANK) {
			for (yT=y;yT<8;yT++){
				
				if (run ==true){
					if (board[xT][yT+1]!=token && board[xT][yT+2]!=token && board[xT][yT+3]!=token
					&& board[xT][yT+4]!=token && board[xT][yT+5]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT][yT+1]!=token && board[xT][yT+2]!=token && board[xT][yT+3]!=token
					&& board[xT][yT+4]!=token && board[xT][yT+5]==token){}
					else if (board[xT][yT+1]!=token && board[xT][yT+2]!=token && board[xT][yT+3]!=token
					&& board[xT][yT+4]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT][yT+1]!=token && board[xT][yT+2]!=token && board[xT][yT+3]!=token
					&& board[xT][yT+4]==token){}
					else if (board[xT][yT+1]!=token && board[xT][yT+2]!=token && board[xT][yT+3]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT][yT+1]!=token && board[xT][yT+2]!=token && board[xT][yT+3]==token){}
					else if (board[xT][yT+1]!=token && board[xT][yT+2]!=token){
						xT=x-1;
						yT=y-1;
						break;
					}
					run=false;
				}
				if (board[xT][yT] != token && board[xT][yT] != BLANK) {
					board[x-1][y-1]=token;
					board[xT][yT]=token;
					activate =true;
				}  else if (board[xT][yT] == BLANK){
					xT=x-1;
					yT=y-1;
					break;
				}
				if (board[xT][yT+1]==BLANK || board[xT][yT+1]==token){
					xT=x-1;
					yT=y-1;
					break;
				}
			}
			if (activate==true){
					activated++;
			} else {
				activate=false;
			}
			run =true;
			xT=x-1;
			yT=y-1;
		}
		/*move Bottom right*/
		if (board[x][y]!=token && board[x][y]!=BLANK) {
			/*if searching side ways use a while loop*//*search bottom right*/
			/*don't use double forloop*/
			while (board[xT+1][yT+1] != token && board[xT+2][yT+2] != BLANK) {
				if (run ==true){
					if (board[xT+1][yT+1]!=token && board[xT+2][yT+2]!=token && board[xT+3][yT+3]!=token
					&& board[xT+4][yT+4]!=token && board[xT+5][yT+5]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT+1]!=token && board[xT+2][yT+2]!=token && board[xT+3][yT+3]!=token
					&& board[xT+4][yT+4]!=token && board[xT+5][yT+5]==token){}
					else if (board[xT+1][yT+1]!=token && board[xT+2][yT+2]!=token && board[xT+3][yT+3]!=token
					&& board[xT+4][yT+4]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT+1]!=token && board[xT+2][yT+2]!=token && board[xT+3][yT+3]!=token
					&& board[xT+4][yT+4]==token){}
					else if (board[xT+1][yT+1]!=token && board[xT+2][yT+2]!=token && board[xT+3][yT+3]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT+1]!=token && board[xT+2][yT+2]!=token && board[xT+3][yT+3]==token){}
					else if (board[xT+1][yT+1]!=token && board[xT+2][yT+2]!=token){
						xT=x-1;
						yT=y-1;
						break;
					}
					run =false;
				}
				if (board[xT][yT] != token ||board[xT+1][yT+1] != token) {
					board[x-1][y-1]=token;	
					board[xT][yT]=token;					
					board[xT+1][yT+1]=token;
					activate =true;
				}else if (board[xT+1][yT+1] == BLANK){
					xT=x-1;
					yT=y-1;
					break;
				}
			xT++;
			yT++;
			}
			if (activate==true){
				activated++;
			} else {
				activate=false;
			}
			run=true;
			xT=x-1;
			yT=y-1;
		}
		/*debugger works for this one (not really) i thnk this works now*/
		/*move bottom left*/
		if (board[x][y-2]!=token && board[x][y-2]!=BLANK) {
			while (board[xT+1][yT-1] != token && board[xT+2][yT-2] != BLANK) {
				if (run ==true) {
					if (board[xT+1][yT-1]!=token && board[xT+2][yT-2]!=token && board[xT+3][yT-3]!=token
					&& board[xT+4][yT-4]!=token && board[xT+5][yT-5]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT-1]!=token && board[xT+2][yT-2]!=token && board[xT+3][yT-3]!=token
					&& board[xT+4][yT-4]!=token && board[xT+5][yT-5]==token){}
					else if (board[xT+1][yT-1]!=token && board[xT+2][yT-2]!=token && board[xT+3][yT-3]!=token
					&& board[xT+4][yT-4]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT-1]!=token && board[xT+2][yT-2]!=token && board[xT+3][yT-3]!=token
					&& board[xT+4][yT-4]==token){}
					else if (board[xT+1][yT-1]!=token && board[xT+2][yT-2]!=token && board[xT+3][yT-3]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT-1]!=token && board[xT+2][yT-2]!=token && board[xT+3][yT-3]==token){}
					else if (board[xT+1][yT-1]!=token && board[xT+2][yT-2]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} 
					run =false;
				}
				if (board[xT][yT] != token ||board[xT+1][yT-1] != token) {
					board[x-1][y-1]=token;
					board[xT][yT]=token;
					board[xT+1][yT-1]=token;
					activate =true;
				} else if (board[xT+1][yT-1]==BLANK){
					xT=x-1;
					yT=y-1;
					break;
				}
			xT++;
			yT--;
			}
			if (activate==true){
				activated++;
			} else {
				activate=false;
			}
			run=true;
			xT=x-1;
			yT=y-1;
		}
		/*move top right*/
		if (board[x-2][y]!=token && board[x-2][y]!=BLANK) {
			/*if searching side ways use a while loop*/ /*search top right*/
			/*don't use double forloop*/
			while (board[xT-1][yT+1] != token && board[xT-2][yT+2] != BLANK) {
				
				if (run ==true){
					if (board[xT-1][yT+1]!=token && board[xT-2][yT+2]!=token && board[xT-3][yT+3]!=token
					&& board[xT-4][yT+4]!=token && board[xT-5][yT+5]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT+1]!=token && board[xT-2][yT+2]!=token && board[xT-3][yT+3]!=token
					&& board[xT-4][yT+4]!=token && board[xT-5][yT+5]==token){}
					else if (board[xT-1][yT+1]!=token && board[xT-2][yT+2]!=token && board[xT-3][yT+3]!=token
					&& board[xT-4][yT+4]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT+1]!=token && board[xT-2][yT+2]!=token && board[xT-3][yT+3]!=token
					&& board[xT-4][yT+4]==token){}
					else if (board[xT-1][yT+1]!=token && board[xT-2][yT+2]!=token && board[xT-3][yT+3]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT+1]!=token && board[xT-2][yT+2]!=token && board[xT-3][yT+3]==token){}
					else if (board[xT-1][yT+1]!=token && board[xT-2][yT+2]!=token){
						xT=x-1;
						yT=y-1;
						break;
					}
					run =false;
				}
				if (board[xT][yT] != token||board[xT-1][yT+1] != token) {
					board[x-1][y-1]=token;
					board[xT-1][yT+1]=token;
					activate =true;
				}else if (board[xT-1][yT+1] == BLANK){
					xT=x-1;
					yT=y-1;
					break;
				}
			xT--;
			yT++;
			}
			if (activate==true){
				activated++;
			} else {
				activate=false;
			}
			run = true;
			xT=x-1;
			yT=y-1;
		}
		/*move top left*/
		if (board[x-2][y-2]!=token && board[x-2][y-2]!=BLANK ) {
			while (board[xT-1][yT-1] != token && board[xT-1][yT-1] != BLANK) {
				if (run == true) {
					if (board[xT-1][yT-1]!=token && board[xT-2][yT-2]!=token && board[xT-3][yT-3]!=token
					&& board[xT-4][yT-4]!=token && board[xT-5][yT-5]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT-1]!=token && board[xT-2][yT-2]!=token && board[xT-3][yT-3]!=token
					&& board[xT-4][yT-4]!=token && board[xT-5][yT-5]==token){}
					else if (board[xT-1][yT-1]!=token && board[xT-2][yT-2]!=token && board[xT-3][yT-3]!=token
					&& board[xT-4][yT-4]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT-1]!=token && board[xT-2][yT-2]!=token && board[xT-3][yT-3]!=token
					&& board[xT-4][yT-4]==token){}
					else if (board[xT-1][yT-1]!=token && board[xT-2][yT-2]!=token && board[xT-3][yT-3]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT-1]!=token && board[xT-2][yT-2]!=token && board[xT-3][yT-3]==token) {}
					else if (board[xT-1][yT-1]!=token && board[xT-2][yT-2]!=token){
						xT=x-1;
						yT=y-1;
						break;
					}
					run = false;
				}
				if (board[xT][yT] != token||board[xT-1][yT-1] != token) {
					board[x-1][y-1]=token;
					board[xT-1][yT-1]=token;
					board[xT][yT]=token;
					activate =true;
				} else if (board[xT-1][yT-1]==BLANK){
					xT=x-1;
					yT=y-1;
					break;
				}
			xT--;
			yT--;
			}
			if (activate==true){
				activated++;
			} else {
				activate=false;
			}
			run = true;
			xT=x-1;
			yT=y-1;
		}
		

		/*move up*/
		if (board[x-2][y-1]!=token && board[x-2][y-1]!=BLANK) {
			for (xT=x-2;xT>1;xT--){
				if (board[xT-1][yT]==BLANK) {
					xT=x-1;
					yT=y-1;
					break;
				}
				if (run ==true){
					if (board[xT-1][yT]!=token && board[xT-2][yT]!=token && board[xT-3][yT]!=token
					&& board[xT-4][yT]!=token && board[xT-5][yT]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT]!=token && board[xT-2][yT]!=token && board[xT-3][yT]!=token
					&& board[xT-4][yT]!=token && board[xT-5][yT]==token){}
					else if (board[xT-1][yT]!=token && board[xT-2][yT]!=token && board[xT-3][yT]!=token
					&& board[xT-4][yT]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT]!=token && board[xT-2][yT]!=token && board[xT-3][yT]!=token
					&& board[xT-4][yT]==token){}
					else if (board[xT-1][yT]!=token && board[xT-2][yT]!=token && board[xT-3][yT]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT-1][yT]!=token && board[xT-2][yT]!=token && board[xT-3][yT]==token){}
					else if (board[xT-1][yT]!=token && board[xT-2][yT]!=token ){
						xT=x-1;
						yT=y-1;
						break;
					}
					run = false;
				}
				if (board[xT][yT]!= token && board[xT][yT]!=BLANK ) {
					board[x-1][y-1]=token;
					board[xT][yT]=token;
					activate =true;
				} else if (board[xT][yT]==BLANK){
					xT=x-1;
					yT=y-1;
					break;
				}
				if (board[xT-1][yT]==BLANK || board[xT-1][yT]==token){
					xT=x-1;
					yT=y-1;
					break;
				}
			}
			if (activate==true){
				activated++;
			} else {
				activate=false;
			}
			run =true;
		xT=x-1;
		yT=y-1;
		}
		/*move down*/
		if (board[x][y-1]!=token && board[x][y-1]!=BLANK) {
			for (xT=x;xT<8;xT++){
				if (board[xT+1][yT]==BLANK) {
					xT=x-1;
					yT=y-1;
					break;
				}
				if (run == true){
					if (board[xT+1][yT]!=token && board[xT+2][yT]!=token && board[xT+3][yT]!=token
					&& board[xT+4][yT]!=token && board[xT+5][yT]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT]!=token && board[xT+2][yT]!=token && board[xT+3][yT]!=token
					&& board[xT+4][yT]!=token && board[xT+5][yT]==token){}
					else if (board[xT+1][yT]!=token && board[xT+2][yT]!=token && board[xT+3][yT]!=token
					&& board[xT+4][yT]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT]!=token && board[xT+2][yT]!=token && board[xT+3][yT]!=token
					&& board[xT+4][yT]==token){}
					else if (board[xT+1][yT]!=token && board[xT+2][yT]!=token && board[xT+3][yT]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT]!=token && board[xT+2][yT]!=token && board[xT+3][yT]==token) {}
					else if (board[xT+1][yT]!=token && board[xT+2][yT]!=token){
						xT=x-1;
						yT=y-1;
						break;
					}
					run = false;
				}
				if (board[xT][yT]!=token && board[xT][yT]!=BLANK) {
					board[x-1][y-1]=token;
					board[xT][yT]=token;
					activate =true;
				} else if (board[xT][yT]==BLANK){
					xT=x-1;
					yT=y-1;
					break;
				}
				if (board[xT+1][yT]==BLANK || board[xT+1][yT]==token){
					xT=x-1;
					yT=y-1;
					break;
				}
			}
			if (activate==true){
				activated++;
			} else {
				activate=false;
			}
			run = true;
		xT=x-1;
		yT=y-1;
		}
		
		if (board[xtemp][ytemp-1]!=token && board[xtemp][ytemp-1]!=BLANK) {
			for (yT=y-2;yT>1;yT--){ /*search left */
				if (board[xT][yT-1]==BLANK) {
					xT=x-1;
					yT=y-1;
					break;
				}
				if (run == true) {
					if (board[xT][yT-1]!=token && board[xT][yT-2]!=token && board[xT][yT-3]!=token
					&& board[xT][yT-4]!=token && board[xT][yT-5]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT+1][yT]!=token && board[xT+2][yT]!=token && board[xT+3][yT]!=token
					&& board[xT][yT-4]!=token && board[xT][yT-5]==token){}
					else if (board[xT][yT-1]!=token && board[xT][yT-2]!=token && board[xT][yT-3]!=token
					&& board[xT][yT-4]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT][yT-1]!=token && board[xT][yT-2]!=token && board[xT][yT-3]!=token
					&& board[xT][yT-4]==token){}
					else if (board[xT][yT-1]!=token && board[xT][yT-2]!=token && board[xT][yT-3]!=token){
						xT=x-1;
						yT=y-1;
						break;
					} else if (board[xT][yT-1]!=token && board[xT][yT-2]!=token && board[xT][yT-3]==token){}
					else if (board[xT][yT-1]!=token && board[xT][yT-2]!=token){
						xT=x-1;
						yT=y-1;
						break;
					}
					run = false;
				}
				if (board[xT][yT] != token && board[xT][yT] != BLANK) {
					board[x-1][y-1]=token;
					board[xT][yT]=token;	
					activate=true;						
				}  else if (board[xT][yT] == BLANK){
					xT=x-1;
					yT=y-1;
					break;
				}
				if (board[xT][yT-1]==BLANK || board[xT][yT-1]==token){
					xT=x-1;
					yT=y-1;
					break;
				}
			}
			if (activate==true){
				activated++;
			} else {
				activate=false;
			}
			run = true;
		xT=x-1;
		yT=y-1;
		}

		if (activated!=0 && activate ==true){
			activated=0;
			activate=false;
			return true;
		}
	}
	activated=0;
	activate=false;
    return false;
}


/**
 * Simply counts how many locations contain the token specified on board.
 **/
unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token)
{
	int x=0;
	int y=0;
	unsigned counter=0;
	/*pretty much increments the variable counter when ever detects the player's token
	it then returns this value as a score*/
	for (x=0;x<8;x++){
		for(y=0;y<8;y++){
			if (board[x][y]==token){
				counter++;
			}
		}
	}
	return counter;
}

/**
 * Swaps the two player pointers so that first points to second and vice versa.
 **/
void swapPlayers(Player ** first, Player ** second)
{
	/*swaps the player's pointers by using an additional third pointer called temp*/
    Player *temp = *first;
    *first=*second;
    *second = temp;
 }
