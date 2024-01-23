#include "tetris.h"

void print_game(int score, Struct *current, char Table[ROWS][COLUMNS])
{
	char Buffer[ROWS][COLUMNS] = {0};
	int i, j;
	char str[] = "42 Tetris";
	for(i = 0; i < current->width; i++){
		for(j = 0; j < current->width; j++){
			if(current->array[i][j])
				Buffer[current->row + i][current->col + j] = current->array[i][j];
		}
	}
	clear();
	for(i = 0; i < COLUMNS - strlen(str) / 2 - 1; i++)
		printw(" ");
	printw("%s\n", str);
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? '#' : '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", score);
}

void print_game_over(int final_score, char Table[ROWS][COLUMNS]) {
	int i, j;
	for(i = 0; i < ROWS; i++) {
		for(j = 0; j < COLUMNS; j++) {
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final_score);
}