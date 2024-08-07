/*
Rock Paper C-issors
Created by Nan0MK

Once, for school, I created a Rock Paper Scissors game in python.
I am now trying to replicate it in C
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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

const char* msg_mainMenu = (
	"Rock Paper C-issors!\n"
	"\n"
	"(1 or P). PLAY\n"
	"(2 or Q). QUIT\n"
);

const char* msg_replayMenu = (
	"Want to play again?\n"
	"\n"
	"(1 or P). PLAY AGAIN\n"
	"(2 or Q). QUIT\n"
);

//__Splashes__//
const char* splash_0 = "Against an AI?!!\n";
const char* splash_1 = "So you think you're smarter than a 5'th grader\n";
const char* splash_2 = "Also try Minetest\n";
const char* splash_3 = "Remember The Alamo!\n";
const char* splash_4 = "Do you even lift bro?\n";
const char* splash_5 = "Made by Na0MK!\n";
const char* splash_6 = "ROCK! PAPER! SCISSORS!\n";
const char* splash_7 = "\"Let\'s go Brandon, I agree\"\n";
const char* splash_8 = "I use Windows, by the way!\n";
const char* splash_9 = "You use Arch By The Way??\n";
const char* splash_10 = "Welcome to my game...\n";
const char* splash_11 = "GOD > Space suit\n";
const char* splash_12 = "USA! USA! USA!\n";
const char* splash_13 = "I like trains!\n";
const char* splash_14 = "Do you no da wae?\n";
const char* splash_15 = "Python to C\n";
const char* splash_16 = "Parkour!!\n";
const char* splash_17 = "A less bloated alternative to connect 4\n";
const char* splash_18 = "This is not made in React?!\n";
const char* splash_19 = "FIGHT! FIGHT! FIGHT!\n";
const char* splash_20 = "Blazingly Fast!!\n";
const char* splash_21 = "\"Brazil mentioned!\"\n";

const char* splashHolder[21] = {
	&splash_0,
	&splash_1,
	&splash_2,
	&splash_3,
	&splash_4,
	&splash_5,
	&splash_6,
	&splash_7,
	&splash_8,
	&splash_9,
	&splash_10,
	&splash_11,
	&splash_12,
	&splash_13,
	&splash_14,
	&splash_15,
	&splash_16,
	&splash_17,
	&splash_18,
	&splash_19,
	&splash_20,
	&splash_21,
};

//__Victory Messages__//
const char* vMsg_0 = "YOU WINNED\n";
const char* vMsg_1 = "A gold medal for you!\n";
const char* vMsg_2 = "GG...\n";
const char* vMsg_3 = "Human Inside!\n";
const char* vMsg_4 = "He\'s fast!\n";
const char* vMsg_5 = "NANI!?\n";
const char* vMsg_6 = "You Won!\n";
const char* vMsg_7 = "Hip, hip, horray! The player saved the day!!\n";
const char* vMsg_8 = "You have killed moor's law!!\n";
const char* vMsg_9 = "You must have cleaned your room!\n";

const char* vmsgHolder[9] = {
	&vMsg_0,
	&vMsg_1,
	&vMsg_2,
	&vMsg_3,
	&vMsg_4,
	&vMsg_5,
	&vMsg_6,
	&vMsg_7,
	&vMsg_8,
	&vMsg_9,
};

//__Defeat Messages__//
const char* dMsg_0 = "Lol\n";
const char* dMsg_1 = "Get good scrub\n";
const char* dMsg_2 = "You have lost to the paperclip machine...\n";
const char* dMsg_3 = "The AI takeover has begun!!\n";
const char* dMsg_4 = "It's a skill issue\n";
const char* dMsg_5 = "Did the Coputer pour water on your cirsuits?\n";
const char* dMsg_6 = "You must have not cleaned your room!\n";
const char* dMsg_7 = "C'mon, man!\n";

const char* dMsgHolder[7] = {
	&dMsg_0,
	&dMsg_1,
	&dMsg_2,
	&dMsg_3,
	&dMsg_4,
	&dMsg_5,
	&dMsg_6,
	&dMsg_7,
};
//___________________//

//_________________________________

//________Codes________
const char* code_clear = "\033[2J\033[H";
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

//Countdown
void countdown(int secconds){
	int i = secconds;
	while(i > 0){
		printf("%s",code_clear);
		printf("%d",i);
		fflush(stdout);
		sleep(1);
		i = i-1;
	}
	sleep(1);
	printf("%s",code_clear);

}
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
//Throw hands for Player
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
//Throw hands for Computer
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

void mainMenu(){
	printf("s",msg_mainMenu);
}

//________Main Game Loop________
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
//_________________________________


int main(void){
	// struct Player thePlayer = createPlayer("Samuel Brandard");

	// printf("Player's name is: %s\nPlayer's score is: %d\nPlayer's hand is: %s\n", thePlayer.name, thePlayer.score, weaponConverter(thePlayer.hand));
	// throwHands(&thePlayer);
	mainMenu();
	//countdown(5);
	//game();


	return 0;
}
