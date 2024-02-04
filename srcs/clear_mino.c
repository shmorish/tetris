#include "tetris.h"

static int	decrease_time = 1000;

static bool is_row_complete(const t_tetris *tetris, int row)
{
	for (int col_i = 0; col_i < COLUMNS; col_i++)
	{
		if (tetris->table[row][col_i] == 0)
			return (false);
	}
	return (true);
}

static void	remove_row(t_tetris *tetris, int row)
{
	for (int col_i = 0; col_i < COLUMNS; col_i++)
	{
		tetris->table[row][col_i] = 0;
	}
}

static void	shift_rows_down(t_tetris *tetris, int empty_row)
{
	int row_i;
	int col_i;

	row_i = empty_row;
	while (row_i > 0)
	{
		col_i = 0;
		while (col_i < COLUMNS)
		{
			tetris->table[row_i][col_i] = tetris->table[row_i - 1][col_i];
			col_i++;
		}
		row_i--;
	}
}

int	clear_mino(t_tetris *tetris)
{
	int	clear_row_count;

	clear_row_count = 0;
	for (int row_i = 0; row_i < ROWS; row_i++)
	{
		if (is_row_complete(tetris, row_i))
		{
			clear_row_count++;
			remove_row(tetris, row_i);
			shift_rows_down(tetris, row_i);
			if (decrease_time > 0)
			{
				tetris->time_to_execute -= decrease_time;
				decrease_time--;
			}
			// 再検証を行うためにインデックスをデクリメント
			row_i--;
		}
	}
	return (clear_row_count * SCORE_PER_BLOCK * COLUMNS);
}
