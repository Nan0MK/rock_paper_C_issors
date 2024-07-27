#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//________Messages________
const char* msg_throwHands = (
	"Choose a weapon:\n"
	"(1 or R). ROCK\n"
	"(2 or P). PAPER\n"
	"(3 or S). SCISSORS\n"
);

const char* msg_pickName = (
	"Pick Your Name\n"
	"Name: "
);

//
//_________________________________


//________Utilities________
typedef enum LogicSignal{
	P1_WIN,
	P2_WIN,
	LS_TIE,
}LogicSignal;

typedef enum GameState{
	GS_PLAY,
	GS_WIN,
	GS_TIE,
	GS_STOP,
}GameState;
//_________________________________

//________Weapon_Stuff________
typedef enum Weapon{
	ROCK,
	PAPER,
	SCISSORS,
	NONE,
}Weapon;

const char* weaponConverter(Weapon hand){
	const char* outp = "";
	if(hand == ROCK){
		outp = "ROCK";
	}
	if(hand == PAPER){
		outp = "PAPER";
	}
	if(hand == SCISSORS){
		outp = "SCISSORS";
	}
	if(hand == NONE){
		outp = "No Hand Selected";
	}
	return outp;
}
//_________________________________

//________Player________
typedef struct Player{
	const char* name;
	int score;
	Weapon hand;
}Player;

Player createPlayer(const char* name){
	Player newPlayer;
	newPlayer.name = name;
	newPlayer.score = 0;
	newPlayer.hand = NONE;

	return newPlayer;
}
//_________________________________


//________Utility_Functions________
void throwHands(Player *player){
	printf("%s",msg_throwHands);
	printf("HAND: ");
	char choice[9];
	scanf("%8s", choice);

	if(strcmp(choice, "1") == 0|| strcmp(choice, "R") == 0|| strcmp(choice, "r") == 0||
		strcmp(choice, "rock") == 0|| strcmp(choice, "ROCK") == 0|| strcmp(choice, "Rock") == 0)
		{
		player->hand = ROCK;
		printf("You picked \'%s\'!\n", weaponConverter(player->hand));
	}

	else if(strcmp(choice, "2") == 0|| strcmp(choice, "P") == 0|| strcmp(choice, "p") == 0||
		strcmp(choice, "paper") == 0|| strcmp(choice, "PAPER") == 0|| strcmp(choice, "Paper") == 0)
		{
		player->hand = PAPER;
		printf("You picked \'%s\'!\n", weaponConverter(player->hand));
	}

	else if(strcmp(choice, "3") == 0|| strcmp(choice, "S") == 0|| strcmp(choice, "s") == 0||
		strcmp(choice, "scissors") == 0|| strcmp(choice, "SCISSORS") == 0|| strcmp(choice, "Scissors") == 0)
		{
		player->hand = SCISSORS;
		printf("You picked \'%s\'!\n", weaponConverter(player->hand));
	}

	else{
		player->hand = NONE;
		printf("\'%s\' is not valid in Rock Paper Scissors!\n", choice);
	}
}

void autoThrowHands(Player *player){
	int max = 3;
	int min = 1;

	int c = rand() % (max - min + 1) + min;

	switch (c)
	{
	case 1:
		player->hand = ROCK;
		break;
	case 2:
		player->hand = PAPER;
		break;
	case 3:
		player->hand = SCISSORS;
		break;
	
	default:
		printf("ERROR WITH autoThrowHands");
		break;
	}
}
//_________________________________

// This is to compare weather the player's and the cpu's hands match or not, then to return the proper signal.
LogicSignal logicManager(Player *player1, Player *player2){
	if(strcmp(weaponConverter(player1->hand), weaponConverter(ROCK))==0 && strcmp(weaponConverter(player2->hand), weaponConverter(SCISSORS))==0 ||
	strcmp(weaponConverter(player1->hand), weaponConverter(PAPER))==0 && strcmp(weaponConverter(player2->hand), weaponConverter(ROCK))==0 ||
	strcmp(weaponConverter(player1->hand), weaponConverter(SCISSORS))==0 && strcmp(weaponConverter(player2->hand), weaponConverter(PAPER))==0){
		return P1_WIN;
	}
	else if(strcmp(weaponConverter(player2->hand), weaponConverter(ROCK))==0 && strcmp(weaponConverter(player1->hand), weaponConverter(SCISSORS))==0 ||
	strcmp(weaponConverter(player2->hand), weaponConverter(PAPER))==0 && strcmp(weaponConverter(player1->hand), weaponConverter(ROCK))==0 ||
	strcmp(weaponConverter(player2->hand), weaponConverter(SCISSORS))==0 && strcmp(weaponConverter(player1->hand), weaponConverter(PAPER))==0){
		return P2_WIN;
	}
	else if(strcmp(weaponConverter(player1->hand), weaponConverter(player2->hand))==0){
		return LS_TIE;
	}
	else{printf("LOGIC MANAGER ERROR!\n");}
}

GameState handThrowing(Player *player, Player *computer){
	LogicSignal winnerIs = logicManager(player, computer);
		switch (winnerIs){
		case P1_WIN:
			printf("Player wins with %s!\n",weaponConverter(player->hand));
			player->score = player->score + 1;
			return GS_WIN;
			break;
		
		case P2_WIN:
			printf("CPU wins with %s!\n",weaponConverter(computer->hand));
			computer->score = computer->score + 1;
			return GS_WIN;
			break;
		
		case LS_TIE:
			printf("TIE! Player chose %s.\nCPU chose %s.\n",weaponConverter(player->hand), weaponConverter(computer->hand));
			return GS_TIE;
			break;
		
		default:
			printf("%s: %s\n%s: %s\n", player->name, weaponConverter(player->hand), computer->name, weaponConverter(computer->hand));
			printf("I don't know what just happened!");
			return GS_STOP;
			break;
		}
}

void game(){
	// Player chooses name
	printf("%s",msg_pickName);
	char choice[51];
	scanf("%50s", choice);

	Player player0 = createPlayer(choice);
	printf("You chose the name: %s\n", player0.name);
	Player computer = createPlayer("CPU");

	GameState gs = GS_PLAY;

	while(gs != GS_STOP){
		autoThrowHands(&computer);
		throwHands(&player0);

		gs = handThrowing(&player0, &computer);

		if(gs == GS_WIN){
			if(player0.score == computer.score + 2){
				printf("PLAYER WINS THIS ROUND\n");
				// Play again menu
				gs = GS_STOP;
			}
			else if(computer.score == player0.score + 2){
				printf("CPU WINS THIS ROUND\n");
				// Play again menu
				gs = GS_STOP;
			}
		}
		else if(gs == GS_TIE){
			printf("TIE");
		}
		
	}
}


int main(void){
	// struct Player thePlayer = createPlayer("Samuel Brandard");

	// printf("Player's name is: %s\nPlayer's score is: %d\nPlayer's hand is: %s\n", thePlayer.name, thePlayer.score, weaponConverter(thePlayer.hand));
	// throwHands(&thePlayer);
	game();


	return 0;
}
