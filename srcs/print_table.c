#include "tetris.h"

# define GAME_TITLE "42 Tetris"

static void	print_title(void)
{
	int	space_len_until_title;

	space_len_until_title = COLUMNS - strlen(GAME_TITLE) / 2 - 1;
	clear();
	for (int i = 0; i < space_len_until_title; i++)
		output(printwwrapper, " ");
	output(printwwrapper, "%s\n", GAME_TITLE);
}

static void print_table_with_falling_mino(const OutFunc outFunc, const t_table *table, int score, char **empty_map_with_mino)
{
	for (int row_i = 0; row_i < ROWS; row_i++)
	{
		for (int col_i = 0; col_i < COLUMNS; col_i++)
			output(outFunc, "%c ", (table->table_array[row_i][col_i] || empty_map_with_mino[row_i][col_i]) ? MAP_FULL : MAP_EMPTY);
		output(outFunc, "\n");
	}
	if (outFunc == printwwrapper)
		output(outFunc, "\nGame over!\n");
	output(outFunc, "\nScore: %lu\n", score);
}


static char	**store_mino(const t_mino *mino, int row, int col)
{
	char	**empty_map_with_mino;

	empty_map_with_mino = init_table();
	put_mino_data_to_table(empty_map_with_mino, (const char **)mino->mino_array, \
		row, col, mino->mino_size);
	return (empty_map_with_mino);
}

void	print_table(const OutFunc outFunc, const t_mino *mino, int score)
{
	char	**empty_map_with_mino;

	empty_map_with_mino = store_mino(mino, mino->current_row, mino->current_col);
	if (outFunc == printwwrapper)
		print_title();
	print_table_with_falling_mino(outFunc, mino, score, empty_map_with_mino);
	free_array(empty_map_with_mino);
}
