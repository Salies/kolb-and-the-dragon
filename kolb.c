#include <stdio.h>
#include "rlutil.h"

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

int main(){
	int i, g, res, textNumber;
	char a;
	saveDefaultColor();

	const char * texts[17] = {
		"Kolb was a brave Nord warrior. One day his Chief asked Kolb to slay an evil dragon that threatened their village. \"Go through the mountain pass, Kolb\", his Chief said. \"You will find the Dragon on the other side\".\n",
		"Kolb took his favorite axe and shield and walked to the pass, where he found a cold cave, a windy cave, and a narrow trail.", //page 2
		"Kolb stepped onto a rocky hill. He could see the dragon sleeping below, and a tavern off a road nearby.", //3
		"Following the stench, Kolb found a filthy orc! The orc snarled and charged Kolb with his spiked club.", //4
		"Treading through the marsh, Kolb discovered a wailing ghost blocking his way.", //5
		"The head of the axe lodged itself in the tough, scaly neck of the beast. It wailed and thrashed, but Kolb held on and eventually sawed through the neck, killing the beast. Kolb returned home victorious, and his village was never bothered by the dragon again.\n\nTHE END",
		"Leaving the marsh behind him, Kolb could see the dragon's lair nearby, as well as a small, welcoming tavern.",
		"A strong gust of wind blew Kolb's torch out, and knocked him into a pit where he split his head and died.\nTHE END",
		"The orc cackled as his club splintered Kolb's shield and smashed into his face. There Kolb died, and the orc had soup from his bones.\n\nTHE END",
		"Kolb remembered a story his Gran told him and tossed two gold chits for the ghost, and it faded away allowing him to pass.",
		"Kolb crept towards the belly of the beast, but no sooner had he taken his eyes off the head of the beast than it snapped him up and ate him whole, axe and all.\n\nTHE END",
		"Climbing up, Kolb found a camp. He met a wise man who shared bread and showed two paths to the dragon's lair. One went through the hills, the other through a marsh.", //12
		"Before the orc could strike, Kolb swung his mighty axe. The orc's head and club fell uselessly to the floor.",
		"Kolb stopped at the tavern to rest before fighting the dragon. High elves ran the tavern, however, and poisoned his mead so they could steal his gold.\n\nTHE END",
		"Kolb swung his axe as hard as he could, but the ghost hardly seemed to notice. The ghost drifted into Kolb, and a deep sleep took him over, from which he never awoke.\n\nTHE END",
		"Kolb found the lair where the dragon slept, tendrils of smoke wafting from its nostrils. The air made Kolb's eyes sting, and he nearly slipped on the bones of men, picked clean. The beast lay on its side, the throat and belly both waiting targets.",
		"Kolb stepped into the frozen cave, but his Nord blood kept him warm. A smelly tunnel climbed a head of him, and wind howled from another to his left. A ladder was nearby as well."//17
	};
	
	const char * paths[16][3][2] = {
		{{"Enter the cold cave", "17"},{"Enter the windy cave", "8"},{"Walk up the trail", "12"}},
		{{"Climb down", "16"},{"Visit tavern", "14"},},
		{{"Raise Shield", "9"},{"Swing Axe", "13"}},
		{{"Attack Ghost", "15"},{"Give Gold", "10"}},
		{{0}},
		{{"Go to the Lair", "16"},{"Go to Tavern", "14"}},
		{{0}},
		{{0}},
		{{"Turn to Page", "7"}},
		{{0}},
		{{"Take the hills", "3"},{"Take the marsh", "5"}},
		{{"Turn to Page", "3"}},
		{{0}},
		{{0}},
		{{"Strike the Neck", "6"},{"Strike the Belly", "11"}},
		{{"Take the smelly tunne", "4"},{"Take the windy tunnel", "8"},{"Climb the ladder", "12"}}
	};
	
	int validNumbers[16][3] = {{17, 8, 12},{16, 14},{9, 13},{15, 10},{0},{16, 14},{0},{0},{7},{0},{3, 5},{3},{0},{0},{6, 11},{4, 8, 12}};
	
	int gameOver[5] = {8, 9, 11, 14, 15};

	int repeat[2][2] = {
		{'y', 'Y'},
		{'n', 'N'}
	};

	void wait(message){
		printf_s("%s", message);
		getchar();
		printf_s("\n");
	}
	
	void start(){
		setColor(11);
		printf_s("Kolb & the Dragon\n");
		resetColor();
		printf_s("An Adventure for Nord Boys\n\n");
		wait("Press enter to start...");
	}
	
	void text(number){
		printf_s("%s\n", texts[number]);
	}
	
	void printOptions(number){
		for(i=0;i<3;i++){
			const char * optionText = paths[number][i][0];
			const char * optionNumber = paths[number][i][1];
			if(optionText==NULL || optionNumber==NULL){
				break; //continue would also be valid, but since there isn't anything after it finds a null array I decided to just use break (continue would loop again just to find out it ended)
			}
			printf_s("\n%s(", optionText);
			setColor(10);
			printf_s("%s", optionNumber);
			resetColor();
			printf_s(")");
		}
	}
	
	int page(n){
		textNumber = n - 1;
		g = n - 2;
		
		void end(color, message, prompt){
			setColor(color);
			printf_s("\n%s", message);
			resetColor();
			printf_s(" %s (y/n) ", prompt);
			scanf_s(" %c", &a);
			getchar();
			for(i=0;i<4;i++){
				if(a==repeat[0][i]){
					clear();
					text(0);
					page(2);
				}
				else if(a==repeat[1][i]){
					exit(0);
				}
			}
			end(color, message, prompt);
		}
		
		if(n==6){
			text(textNumber);
			end(10, "You Won!", "Play again?");
		}
		
		void ask(number){
			printf_s("\n\nWhat will Kolb do? ");
			scanf_s("%d", &res);
			printf_s("\n");
			//validate
			for(i=0;i<3;i++){
				if(res!=0){
					if(validNumbers[number][i]==res){
						page(res);
					}
					else if(n==16 && res==69){
						printf_s("Oh no! Kolb encountered the infamous Ghost Fapping Little Gang! The Chubby That Skids On The Gala kills him with a deadly ectoplasmic attack.\n\nTHE END\n");
						end(12, "Game Over.", "Start a new game?");
					}
					else if(n==16 && res==666){
						printf_s("A demon spawns and kills Kolb.\n\nTHE END\n");
						end(12, "Game Over.", "Start a new game?");
					}
				}
			}
			printf_s("Invalid answer. Please enter one of the green option numbers.");
			ask(number);
		}
		
		for(i=0;i<5;i++){
			if(n==gameOver[i]){
				text(textNumber);
				end(12, "Game Over.", "Start a new game?");
				break;
			}
		}
		
		text(textNumber);
		printOptions(g);
		ask(g);
	}
	
	start();
	text(0);
	wait("Press enter to continue...");
	page(2);
	
	return 0;
}
