#include "snake.h"

void setScore() 
{
	char strScore[14] = {'[', 's', 'c', 'o', 'r', 'e', ':', ' '};
	strScore[8] = ((score / 10000) + '0');
	strScore[9] = ((score / 1000) % 10 + '0');
	strScore[10] = ((score / 100) % 10 + '0');
	strScore[11] = ((score / 10) % 10 + '0');
	strScore[12] = (score % 10 + '0');
	strScore[13] = ']';
	int start = (RAW_LENGTH - 10) / 2 - 3;
	for (int i = 0; i < 14; i++) {
		field[COLUMN_LENGTH - 1][start + i] = strScore[i]; 
	}
}

void calculateScore()
{
	score += rand() % 6 + 20;
}

void help() 
{
	printf("\ec");
	printf("Hotkeys: '%c' - move up\n", KEY_UP);
	printf("         '%c' - move down\n", KEY_DOWN);
	printf("         '%c' - move left\n", KEY_LEFT);
	printf("         '%c' - move right\n", KEY_RIGHT);
	printf("         '%c' - pause game\n", KEY_PAUSE);
	printf("         '%c' - forced exit to main menu\n", KEY_EXIT);
	printf("\nRules of the game are quite simple and do not differ from the original game.\n");
	printf("You need to score as many points. Points are awarded for the capture of food.\n");
	printf("You can walk through border (%c - border cell), but if the snake eats itself,\n", BORDER_CELL);
	printf("or crashes into a wall (%c - wall cell), you lose.\n", WALL_CELL);
	printf("\nYou can also change the map. To do this, you need to change the files\n");
	printf("in the './res/levels' folder with the extension '.lvl'\n");
    printf("\nPress any key to return to the main menu...\n");
	getchar();
}

void options()
{
	printf("\ec");
	printf("1. Choose level\n");
	printf("2. Set delay\n");
	printf("\nPress any key to return to the main menu...\n");

	switch (getchar()) {
		case '1':
			chooseLevel();
			break;
		case '2':
			setDelay();
			break;
	}
}

void showHighScore()
{
	FILE *file;
	file = fopen(HIGH_SCORE, "r");
	if (file == NULL) {
		printf("\ec");
		printf("Error! Can't open the hgih score file '%s'\n", HIGH_SCORE);
		printf("Please check the file name\n");		
		printf("\nPress any key to return to the main menu...\n");

		getchar();

		return;
	} 
	char highScore[80];
	fgets(highScore, 80, file);
	fclose(file);

	printf("\ec");
	printf("High score: %s\n", highScore);
	printf("\nPress any key to return to the main menu...\n");
	getchar();
}

int tryToSetHighScore()
{
	FILE *file;
	file = fopen(HIGH_SCORE, "r");
	if (file == NULL) {
		return 0;
	} 
	char highScore[80];
	fgets(highScore, 80, file);
	fclose(file);

	if (score > strtoint(highScore)) {
		FILE *file;
		file = fopen(HIGH_SCORE, "w");
		fprintf(file, "%d", score);
		fclose(file);
		return 1;
	}

	return 0;
}

void chooseLevel()
{
	printf("\ec");
	printf("1. Level 1 (default)\n");
	printf("2. Level 2\n");
	printf("3. Level 3\n");
	printf("4. Level 4\n");
	printf("5. Level 5\n");
	printf("\nPress any key to return to the main menu...\n");

	switch (getchar()) {
		case '1':
			strcpy(level, LVL1);
			break;
		case '2':
			strcpy(level, LVL2);
			break;
		case '3':
			strcpy(level, LVL3);
			break;
		case '4':
			strcpy(level, LVL4);
			break;
		case '5':
			strcpy(level, LVL5);
			break;
	}
}

void setFieldFromFile(const char* fname) 
{
	FILE *file;
	file = fopen(fname, "r");
	if (file == NULL) {
		printf("\ec");
		printf("Error! Can't open the level file '%s'\n", fname);
		printf("Please check the file name and start the game again\n");		
		printf("\nPress any key to return to the main menu...\n");

		getchar();

		error = 1;
		return;
	} 

	for (int i = 0; i < COLUMN_LENGTH; i++) {
		for (int j = 0; j <= RAW_LENGTH; j++) {
			char ch;
			fscanf(file, "%c", &ch);
			if (j == RAW_LENGTH) {
				continue;
			}
			field[i][j] = ch;
		}
	}
	fclose(file);
	error = 0;
}

void setDelay()
{
	printf("\ec");
	printf("1. 50000 \n");
	printf("2. 100000 (default)\n");
	printf("3. 200000\n");
	printf("4. 300000\n");
	printf("\nPress any key to return to the main menu...\n");

	switch (getchar()) {
		case '1':
			delay = DELAY1;
			break;
		case '2':
			delay = DELAY2;
			break;
		case '3':
			delay = DELAY3;
			break;
		case '4':
			delay = DELAY4;
			break;
	}
}

void pauseGame() 
{
	if (gamePause || gameOver) {
		return;
	}
	gamePause = 1;
	printf("Game is paused. Press any key to continue...\n");
	do {

	} while (!keyIsPressed());
}