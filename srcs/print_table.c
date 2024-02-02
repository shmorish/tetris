#include "tetris.h"

static int	switch_print(bool situation, const char * restrict format, ...)
{
	int		result;
	va_list	args;

	va_start(args, format);
	if (situation == GAME_ON)
		result = vwprintw(stdscr, format, args);
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

static void print_table_from_buffer(bool situation, t_tetris *tetris, int score, char buffer[ROWS][COLUMNS])
{
	for (int row_i = 0; row_i < ROWS; row_i++)
	{
		for (int col_i = 0; col_i < COLUMNS; col_i++)
			switch_print(situation, "%c ", (tetris->table[row_i][col_i] + buffer[row_i][col_i]) ? MAP_FULL : MAP_EMPTY);
		switch_print(situation, "\n");
	}
	if (situation == GAME_OVER)
		switch_print(situation, "\nGame over!\n");
	switch_print(situation, "\nScore: %d\n", score);
}

void	print_table(int situation, t_tetris *tetris, int score)
{
	char	buffer[ROWS][COLUMNS] = {};

	if (situation == GAME_ON)
	{
		for (int height_index = 0; height_index < tetris->mino_size; height_index++)
		{
			for (int width_index = 0; width_index < tetris->mino_size; width_index++)
			{
				if (tetris->mino_data[height_index][width_index])
					buffer[tetris->current_row + height_index][tetris->current_col + width_index] = tetris->mino_data[height_index][width_index];
			}
		}
		print_title();
	}
	print_table_from_buffer(situation, tetris, score, buffer);
}
