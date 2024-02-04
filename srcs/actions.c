#include "tetris.h"

static void update_table(t_tetris *tetris, int row, int col);
static void	generate_new_mino(t_tetris *tetris);
static void	rotate(t_tetris *tetris, int size);

void	rotate_mino(t_tetris *tetris)
{
	t_tetris	*tmp;

	tmp = dup_tetris_struct(tetris);
	rotate(tmp, tetris->mino_size);
	if (can_mino_move(tmp))
		rotate(tetris, tetris->mino_size);
	destroy_struct(tmp);
}

void	move_mino_down(t_tetris *tetris)
{
	t_tetris	*tmp;

	tmp = dup_tetris_struct(tetris);
	tmp->current_row++;
	if (can_mino_move(tmp))
		tetris->current_row++;
	else
	{
		update_table(tetris, tetris->current_row, tetris->current_col);
		tetris->score += clear_mino(tetris);
		generate_new_mino(tetris);
		if (can_mino_move(tetris) == false)
			tetris->game_on = GAME_OVER;
	}
	destroy_struct(tmp);
}

void	move_mino_left(t_tetris *tetris)
{
	t_tetris	*tmp;

	tmp = dup_tetris_struct(tetris);
	tmp->current_col--;
	if (can_mino_move(tmp))
		tetris->current_col--;
	destroy_struct(tmp);
}

void	move_mino_right(t_tetris *tetris)
{
	t_tetris	*tmp;

	tmp = dup_tetris_struct(tetris);
	tmp->current_col++;
	if (can_mino_move(tmp))
		tetris->current_col++;
	destroy_struct(tmp);
}

static void update_table(t_tetris *tetris, int row, int col)
{
    for (int x = 0; x < tetris->mino_size; x++)
        for (int y = 0; y < tetris->mino_size; y++)
            if (tetris->mino_data[x][y] != 0)
                tetris->table[row + x][col + y] = tetris->mino_data[x][y];
}

static void	rotate(t_tetris *tetris, int size)
{
	t_tetris	*tmp;
	int			opposite_index;

	tmp = dup_tetris_struct(tetris);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			opposite_index = size - 1 - j;
			tetris->mino_data[i][j] = tmp->mino_data[opposite_index][i];
		}
	}
	destroy_struct(tmp);
}

static void	generate_new_mino(t_tetris *tetris)
{
	free_array(tetris->mino_data);
	tetris->mino_data = NULL;
	generate_mino(tetris);
}
