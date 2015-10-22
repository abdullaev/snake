#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define COLUMN_LENGTH 21
#define RAW_LENGTH 50
#define RANDOM_Y (rand() % (COLUMN_LENGTH - 2) + 1)
#define RANDOM_X (rand() % (RAW_LENGTH - 2) + 1)
#define DEFAULT_DELAY 100000
#define DELAY1 50000
#define DELAY2 100000
#define DELAY3 200000
#define DELAY4 300000
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_PAUSE ' '
#define KEY_EXIT 'q'
#define BORDER_CELL '#'
#define SNAKE_CELL 'O'
#define FOOD_CELL '$'
#define VOID_CELL ' '
#define WALL_CELL '@'
#define DEAD_CELL 'X'
#define DEFAULT_LVL "res/levels/1.lvl"
#define LVL1 "res/levels/1.lvl"
#define LVL2 "res/levels/2.lvl"
#define LVL3 "res/levels/3.lvl"
#define LVL4 "res/levels/4.lvl"
#define LVL5 "res/levels/5.lvl"
#define HIGH_SCORE "res/highscore.snk"
#define SAVE "res/save.snk"
#define DATA "res/saved_data.snk"

int gameOver;
int gamePause;
int error;

int score;
char level[100];
int delay;

char field[COLUMN_LENGTH][RAW_LENGTH];

int snakeY[(COLUMN_LENGTH - 2) * (RAW_LENGTH - 2)];
int snakeX[(COLUMN_LENGTH - 2) * (RAW_LENGTH - 2)];
int snakeLength;

int foodY;
int foodX;

int stepY;
int stepX;

char choice;

//=====================================
// Основаная механика                 =
//=====================================

void initGame();

void runGame();

void move();

void printField();

void createFood();

char nextCell();

void reverseSnake();

int prevChoiceIsOpposite();

int snakeIsLine();

//=====================================
// Дополнительный функционал          =
//=====================================

void setScore();

void calculateScore();

void help();

void pauseGame();

void options();

void chooseLevel();

void setFieldFromFile(const char* fname);

void setDelay();

void showHighScore();

int tryToSetHighScore();

//=====================================
// Вспомогательные функции            =
//=====================================

int keyIsPressed();

int strtoint_n(char* str, int n);

int strtoint(char* str);

#endif