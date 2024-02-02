#include "tetris.h"

static int	decrease_time = 1000;

static void	rotate(t_tetris *tetris, int size)
{
	t_tetris	*tmp;
	int			oppositeIndex;

	tmp = dup_mino_data(tetris);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			oppositeIndex = size - 1 - j;
			tetris->mino_data[i][j] = tmp->mino_data[oppositeIndex][i];
		}
	}
	destroy_struct(tmp);
}

void	rotate_mino(t_tetris *tetris, t_tetris *tmp)
{
	rotate(tmp, tetris->mino_size);
	if (can_mino_move(tmp, tmp->mino_data))
		rotate(tetris, tetris->mino_size);
}

void	move_mino(t_tetris *tetris, t_tetris *tmp, int direction)
{
	tmp->current_col += direction;
	if (can_mino_move(tmp, tmp->mino_data))
		tetris->current_col += direction;
}

static void	lock_mino(t_tetris *tetris)
{
	for (int i = 0; i < tetris->mino_size; i++)
	{
		for (int j = 0; j < tetris->mino_size; j++)
		{
			if (tetris->mino_data[i][j])
				tetris->table[tetris->current_row + i][tetris->current_col
					+ j] = tetris->mino_data[i][j];
		}
	}
}

static int	is_row_complete(t_tetris *tetris, int row)
{
	for (int m = 0; m < COLUMNS; m++)
	{
		if (tetris->table[row][m] == 0)
		{
			return (0);
		}
	}
	return (1);
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

static int	clear_complete_rows(t_tetris *tetris)
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
	return (clear_row_count * SCORE_PER_BLOCK * ROWS);
}

static void	generate_new_mino(t_tetris *tetris)
{
	free_array(tetris->mino_data);
	tetris->mino_data = NULL;
	generate_mino(tetris);
}

void	move_down(t_tetris *tetris, t_tetris *tmp)
{
	tmp->current_row++;
	if (can_mino_move(tmp, tmp->mino_data))
	{
		tetris->current_row++;
	}
	else
	{
		lock_mino(tetris);
		tetris->score += clear_complete_rows(tetris);
		generate_new_mino(tetris);
		if (!can_mino_move(tetris, tetris->mino_data))
		{
			tetris->game_on = false;
		}
	}
}
