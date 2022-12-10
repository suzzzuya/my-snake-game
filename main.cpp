#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

struct Snake {
	int x;
	int y;
};

struct Fruit {
	int x;
	int y;
};

enum Cell {
	EMPTY_CELL,
	SNAKE_CELL,
	FRUIT_CELL,
};

enum Key {
	SKIP,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	EXIT,
};

int* insertField(int* field, int* width, int* height);
void draw(int* field, int width, int height, int* score);
void setup(int* field, int width, int height, Snake* snake, Fruit* food);
Key input();
void logic(int* field, int width, int height, Snake* snake, Fruit* fruit, Key key, int* score, bool* gameOver);
void genFruit(int* field, int width, int height, Fruit* fruit);

int main(void) {
	int* field = NULL;
	int width = 0;
	int height = 0;
	Snake snake;
	Fruit fruit;
	int score = 0;
	bool gameOver = false;
	
	field = insertField(field, &width, &height);
	system("cls");

	setup(field, width, height, &snake, &fruit);

	while (!gameOver) {
		draw(field, width, height, &score);
		Key key = input();
		logic(field, width, height, &snake, &fruit, key, &score, &gameOver);
	}

	free(field);

	return 0;
}

int* insertField(int* field, int* width, int* height) {
	puts("Type the field size\nRecommended 40x20");

	puts("Width:");
	scanf("%d", width);
	puts("Height:");
	scanf("%d", height);

	field = (int*)malloc(*width * *height * sizeof(int));

	for (int i = 0; i < *height; i++) {
		for (int j = 0; j < *width; j++) {
			field[i * *width + j] = EMPTY_CELL;
		}
	}
	return field;
}

void draw(int* field, int width, int height, int* score) {
	system("cls");
	for (int i = 0; i < height; i++) {
		printf("\n");
		for (int j = 0; j < width; j++) {
			switch (field[i * width + j]) {
			case EMPTY_CELL:
				printf(".");
				break;
			case FRUIT_CELL:
				printf("x");
				break;
			case SNAKE_CELL:
				printf("o");
				break;
			default:
				printf(".");
				break;
			}
		}
	}
	printf("\nSCORE: %d\n", *score);
}

void setup(int* field, int width, int height, Snake* snake, Fruit* fruit) {
	// centering the snake pos

	snake->x = width / 2;
	snake->y = height / 2;

	field[snake->y * width + snake->x] = SNAKE_CELL;

	genFruit(field, width, height, fruit);
}

Key input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'W':
		case 'w':
			return UP;
		case 'A':
		case 'a':
			return LEFT;
		case 'S':
		case 's':
			return DOWN;
		case 'D':
		case 'd':
			return RIGHT;
		case 'Q':
		case 'q':
			return EXIT;
		default:
			return SKIP;
			break;
		}
	}
}

void logic(int* field, int width, int height, Snake* snake, Fruit* fruit, Key key, int* score, bool* gameOver) {
	Sleep(0.05);

	field[snake->y * width + snake->x] = EMPTY_CELL; // clear prev

	switch (key)
	{
	case UP:
		snake->y--;
		break;
	case DOWN:
		snake->y++;
		break;
	case LEFT:
		snake->x--;
		break;
	case RIGHT:
		snake->x++;
		break;
	case EXIT:
		*gameOver = true;
		break;
	default:
		break;
	}
	if (snake->x > width) {
		snake->x = 0;
	}
	if (snake->x < 0) {
		snake->x = width;
	}
	if (snake->y > height) {
		snake->y = 0;
	}
	if (snake->y < 0) {
		snake->y = height;
	}
	field[snake->y * width + snake->x] = SNAKE_CELL;

	if (snake->x == fruit->x && snake->y == fruit->y) { // if you take fruit gen new and score + 1
		genFruit(field, width, height, fruit);
		*score = *score + 1;
	}

}

void genFruit(int* field, int width, int height, Fruit* fruit) {
	fruit->x = rand() % width;
	fruit->y = rand() % height;

	field[fruit->y * width + fruit->x] = FRUIT_CELL;
}