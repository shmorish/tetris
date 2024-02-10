#include "tetris.h"

void print_game(t_mino *current, t_player *player)
{
	char Buffer[ROWS][COLUMNS] = {0};
	int i, j;
	char str[] = "42 Tetris";
	for(i = 0; i < current->mino_size; i++){
		for(j = 0; j < current->mino_size; j++){
			if(current->mino_array[i][j])
				Buffer[current->current_row + i][current->current_col + j] = current->mino_array[i][j];
		}
	}
	clear();
	for(i = 0; i < COLUMNS - strlen(str) / 2 - 1; i++)
		printw(" ");
	printw("%s\n", str);
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			printw("%c ", (player->table->table_array[i][j] + Buffer[i][j]) ? MAP_FULL : MAP_EMPTY);
		}
		printw("\n");
	}
	printw("\nScore: %ld\n", player->table->score);
}

void print_game_over(t_player *player)
{
	int i, j;
	for(i = 0; i < ROWS; i++) {
		for(j = 0; j < COLUMNS; j++) {
			printf("%c ", player->table->table_array[i][j] ? MAP_FULL : MAP_EMPTY);
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %ld\n", player->table->score);
}
