#include "tetris.h"

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
		tetris->score += clear_mino(tetris);
		generate_new_mino(tetris);
		if (!can_mino_move(tetris, tetris->mino_data))
		{
			tetris->game_on = false;
		}
	}
}
