#include "tetris.h"

void print_game(Struct *current, t_player *player)
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
			printw("%c ", (player->table->table_array[i][j] + Buffer[i][j]) ? '#' : '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", player->table->score);
}

void print_game_over(t_player *player)
{
	int i, j;
	for(i = 0; i < ROWS; i++) {
		for(j = 0; j < COLUMNS; j++) {
			printf("%c ", player->table->table_array[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", player->table->score);
}
