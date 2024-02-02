#include "tetris.h"

static int	switch_print(int situation, const char * restrict format, ...)
{
	va_list	args;
	int		result = 0;

	va_start(args, format);
	if (situation == GAME_ON)
		vwprintw(stdscr, format, args);
	else if (situation == GAME_OVER)
		result = vprintf(format, args);
	else
	{
		perror("invalid situation");
		result = ERR;
	}
	va_end(args);
	return (result);
}

static void	print_title(void)
{
	int	space_len_until_title;
	int	space_i;

	space_len_until_title = COLUMNS - strlen(GAME_TITLE) / 2;
	space_i = 0;
	clear();
	while (space_i < space_len_until_title)
	{
		printw(" ");
		space_i++;
	}
	switch_print(GAME_ON, "%s\n", GAME_TITLE);
}

void	print_table(int situation, t_tetris *tetris, int score)
{
	char	Buffer[ROWS][COLUMNS] = {};

	if (situation == GAME_ON)
	{
		for(int i = 0; i < tetris->mino_size; i++) {
			for(int j = 0; j < tetris->mino_size; j++) {
				if(tetris->mino_data[i][j])
					Buffer[tetris->current_row + i][tetris->current_col + j] = tetris->mino_data[i][j];
			}
		}
		print_title();
	}
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (situation == GAME_ON)
				switch_print(situation, "%c ", (tetris->table[i][j] + Buffer[i][j]) ? MAP_FULL : MAP_EMPTY);
			else
				switch_print(situation, "%c ", tetris->table[i][j] ? MAP_FULL : MAP_EMPTY);
		}
		switch_print(situation, "\n");
	}
	if (situation == GAME_OVER)
		switch_print(situation, "\nGame over!\n");
	switch_print(situation, "\nScore: %d\n", score);
}
