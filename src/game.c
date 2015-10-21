#include "snake.h"

void initGame() 
{
	//Инициализация данных
	gameOver = 0;
	gamePause = 0;
	score = 0;
	stepY = 0;
	stepX = 0;
	choice = 0;

	//Инициализируем поле, если возникла ошибка при считывании поля,
	//то выходим из функции 
	setFieldFromFile(level);
	if (error) {
		return;
	}

	//Инициализируем змейку
	snakeLength = 1;
	snakeY[0] = COLUMN_LENGTH / 2;
	snakeX[0] = RAW_LENGTH / 2;
	field[snakeY[0]][snakeX[0]] = SNAKE_CELL;

	//Создаем еду
	createFood();

	//Ставим на поле табличку с счётчиком очков
	setScore();
}

void runGame() 
{
	do {
		do {
			move();
			printField();
			usleep(delay);
		} while(!keyIsPressed() && !gameOver);

		choice = getchar();

		if (gamePause) {
			gamePause = 0;
			if (choice == KEY_PAUSE) {
				choice = 0;
			}
		}

		//Если прошлый выбор был противоположенный,
		//если змейка выстроенна в линию, то разворачиваем её
		//иначе игнорируем выбор
		if (prevChoiceIsOpposite()) {
			if (snakeIsLine()) {
				reverseSnake();
			} else {
				choice = 0;
			}
		}

		switch (choice) {
			case KEY_DOWN:
				stepX = 0;
				stepY = 1;
				break;
			case KEY_UP:
				stepX = 0;
				stepY = -1;
				break;
			case KEY_LEFT:
				stepX = -1;
				stepY = 0;
				break;
			case KEY_RIGHT:
				stepX = 1;
				stepY = 0;
				break;
			case KEY_PAUSE:
 				pauseGame();
				break;
			case KEY_EXIT:
				gameOver = 1;
				break;
			default:
				break;
		}
	} while (!gameOver);
}

void move()
{
	//Если мы собираемся пойти в клетку с едой,
	//то на месте еды дорисовываем голову и создаем новую еду,
	//завершаем функцию
	if (nextCell() == FOOD_CELL) {
		snakeY[++snakeLength - 1] = foodY;
		snakeX[snakeLength - 1] = foodX;
		field[foodY][foodX] = SNAKE_CELL;
		setScore(++score);
		createFood();
		return;
	}

	//Если змейка наткнулась на себя или на стену, игра завершается
	if (nextCell() == SNAKE_CELL && !(stepX == 0 && stepY == 0) || nextCell() == WALL_CELL) {
		gameOver = 1;
	} 

	//Освобождаем хвост змеи, и сдвигаем всю змейку, кроме головы
	field[snakeY[0]][snakeX[0]] = VOID_CELL;
	for (int i = 0; i < snakeLength - 1; i++) {
		snakeX[i] = snakeX[i + 1];
		snakeY[i] = snakeY[i + 1];
	}

	//Двигаем голову змейки на новые координаты
	snakeX[snakeLength - 1] += stepX;
	snakeY[snakeLength - 1] += stepY;

	//Следим, чтобы координаты головы не вышли за границы
	if (snakeX[snakeLength - 1] == RAW_LENGTH - 1) {
		snakeX[snakeLength - 1] = 1;
	}
	if (snakeX[snakeLength - 1] == 0) {
		snakeX[snakeLength - 1] = RAW_LENGTH - 2;
	}
	if (snakeY[snakeLength - 1] == COLUMN_LENGTH - 1) {
		snakeY[snakeLength - 1] = 1;
	}
	if (snakeY[snakeLength - 1] == 0) {
		snakeY[snakeLength - 1] = COLUMN_LENGTH - 2;
	}

	//Ставим змейку на поле
	for (int i = 0; i < snakeLength; i++) {
		field[snakeY[i]][snakeX[i]] = SNAKE_CELL;
	} 
}

void printField()
{
	//Очищаем консоль
	printf("\ec");

	for (int i = 0; i < COLUMN_LENGTH; i++) {
		for (int j = 0; j < RAW_LENGTH; j++) {
			printf("%c", field[i][j]);
		}
		printf("\n");
	}

	if (gameOver) {
		printf("Game Over! Your score: %d\n", score);
		//Пробуем обновить рекорд, если получилось,
		//то оповещаем
		if (tryToSetHighScore()) {
				printf("New record!\n");
		}
		printf("\nPress any key to return main menu...\n");
	}
}

void createFood()
{
	//Присваивем еде случайные координаты, пока клетка не свободна
	do {
		foodY = RANDOM_Y;
		foodX = RANDOM_X;
	} while (field[foodY][foodX] != VOID_CELL);

	field[foodY][foodX] = FOOD_CELL;
}

char nextCell() 
{
	return field[snakeY[snakeLength - 1] + stepY][snakeX[snakeLength - 1] + stepX];
}

void reverseSnake() 
{
	for (int i = 0; i < snakeLength / 2; i++) {
		int tmp = snakeX[i]; 
		snakeX[i] = snakeX[snakeLength - i - 1];
		snakeX[snakeLength - i - 1] = tmp;

		tmp = snakeY[i]; 
		snakeY[i] = snakeY[snakeLength - i - 1];
		snakeY[snakeLength - i - 1] = tmp;
	}
}


int prevChoiceIsOpposite()
{
	return (choice == KEY_UP && stepY == 1 ||
			choice == KEY_DOWN && stepY == -1 ||
			choice == KEY_LEFT && stepX == 1 ||
			choice == KEY_RIGHT && stepX == -1);
}

int snakeIsLine()
{
	int xIsLine = 1;
	int yIsLine = 1;
	for (int i = 1; i < snakeLength; i++) {
		if (snakeX[i] != snakeX[i - 1]) {
			xIsLine = 0;
		}
		if (snakeY[i] != snakeY[i - 1]) {
			yIsLine = 0;
		}
	}
	return (xIsLine || yIsLine);
}