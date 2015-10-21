#include "snake.h"

int main()
{
	//Включаем неканоничный ввод в терминале,
	//чтобы функция getchar() не требовала подтверждения Enter'ом
	system("stty -icanon -echo");

	//Инициаллизируем начальные параметры программы
	srand(time(NULL));
	delay = DEFAULT_DELAY;
	strcpy(level, DEFAULT_LVL);

	int exit = 0;
	do {
		printf("\ec");
		printf("1. New game\n");
		printf("2. High score\n");
		printf("3. Help\n");
		printf("4. Options\n");
		printf("5. Exit\n");

		switch (getchar()) {
			case '1':
				initGame();
				//Если не произошло ошибки при инициаллизации, то запускаем игру
				if (!error) {
					runGame();
				}
				break;
			case '2':
				showHighScore();
				break;
			case '3':
				help();
				break;
			case '4':
				options();
				break;
			case '5':
				exit = 1;
				printf("\ec");
				printf("Goodbye!\n");
				break;
		}
	} while (!exit);

	//Включаем каноничный ввод								 
	system("stty icanon echo"); 

	return 0;
}