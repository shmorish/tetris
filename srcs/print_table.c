#include "tetris.h"

static int	switch_print(const bool situation, const char * restrict format, ...)
{
	int		result = 0;
	va_list	args;

	va_start(args, format);
	if (situation == GAME_ON)
		result = vwprintw(stdscr, format, args);
	else if (situation == GAME_OVER)
		result = vprintf(format, args);
	va_end(args);
	return (result);
}

static void	print_title(void)
{
	int	space_len_until_title;

	space_len_until_title = COLUMNS - strlen(GAME_TITLE) / 2 - 1;
	clear();
	for (int i = 0; i < space_len_until_title; i++)
		switch_print(GAME_ON, " ");
	switch_print(GAME_ON, "%s\n", GAME_TITLE);
}

static void print_table_with_falling_mino(const bool situation, const t_tetris *tetris, int score, char **buffer)
{
	for (int row_i = 0; row_i < ROWS; row_i++)
	{
		for (int col_i = 0; col_i < COLUMNS; col_i++)
			switch_print(situation, "%c ", (tetris->table[row_i][col_i] + buffer[row_i][col_i]) ? MAP_FULL : MAP_EMPTY);
		switch_print(situation, "\n");
	}
	if (situation == GAME_OVER)
		switch_print(situation, "\nGame over!\n");
	switch_print(situation, "\nScore: %lu\n", score);
}

static char	**store_mino(const t_tetris *tetris)
{
	char	**empty_map_with_mino;

	empty_map_with_mino = init_table();
	for (int height_index = 0; height_index < tetris->mino_size; height_index++)
	{
		for (int width_index = 0; width_index < tetris->mino_size; width_index++)
		{
			if (tetris->mino_data[height_index][width_index])
				empty_map_with_mino[tetris->current_row + height_index][tetris->current_col + width_index] = tetris->mino_data[height_index][width_index];
		}
	}
	return (empty_map_with_mino);
}

void	print_table(const bool situation, const t_tetris *tetris, int score)
{
	char	**empty_map_with_mino;

	empty_map_with_mino = store_mino(tetris);
	if (situation == GAME_ON)
		print_title();
	print_table_with_falling_mino(situation, tetris, score, empty_map_with_mino);
	free_array(empty_map_with_mino);
}
