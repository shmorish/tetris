#include "tetris.h"

static int	decrease_time = 1000;

static bool is_row_complete(t_tetris *tetris, int row)
{
	for (int m = 0; m < COLUMNS; m++)
	{
		if (tetris->table[row][m] == 0)
			return (false);
	}
	return (true);
}

static void	remove_row(t_tetris *tetris, int row)
{
	for (int l = 0; l < COLUMNS; l++)
	{
		tetris->table[row][l] = 0;
	}
}

static void	shift_rows_down(t_tetris *tetris, int start_row)
{
	for (int k = start_row; k >= 1; k--)
		for (int l = 0; l < COLUMNS; l++)
			tetris->table[k][l] = tetris->table[k - 1][l];
}

int	clear_mino(t_tetris *tetris)
{
	int	clear_row_count;

	clear_row_count = 0;
	for (int n = 0; n < ROWS; n++)
	{
		if (is_row_complete(tetris, n))
		{
			clear_row_count++;
			remove_row(tetris, n);
			shift_rows_down(tetris, n);
			if (decrease_time > 0)
			{
				tetris->time_to_execute -= decrease_time;
				decrease_time--;
			}
			// 再検証を行うためにインデックスをデクリメント
			n--;
		}
	}
	return (clear_row_count * SCORE_PER_BLOCK * COLUMNS);
}
