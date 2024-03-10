#include "mino.h"

static void	rotate_tetromino(t_mino *mino)
{
	t_mino	*tmp;

	tmp = duplicate_mino(mino);
	for (int h_i = 0; h_i < mino->mino_size; h_i++)
	{
		for (int w_i = 0, opposite_h_i = mino->mino_size - 1; w_i < mino->mino_size; w_i++, opposite_h_i--)
			mino->mino_array[h_i][w_i] = tmp->mino_array[opposite_h_i][h_i];
	}
	free_mino(tmp);
}

void	rotate_mino(t_player *player)
{
	t_mino	*mino_checker;

	mino_checker = duplicate_mino(player->mino);
	rotate_tetromino(mino_checker);
	if (is_game_on(mino_checker, player->table->table_array))
		rotate_tetromino(player->mino);
	free_mino(mino_checker);
}

void	move_mino_down(t_player *player)
{
	t_mino	*mino_checker;

	mino_checker = duplicate_mino(player->mino);
	mino_checker->current_row++;
	if (is_game_on(mino_checker, player->table->table_array))
		player->mino->current_row++;
	else
	{
		store_mino_to_table(player->mino, player->table->table_array);
		player->table->score += clear_mino(player);
		generate_new_mino(player->mino);
	}
	free_mino(mino_checker);
}

void	move_mino_left(t_player *player)
{
	t_mino	*mino_checker;

	mino_checker = duplicate_mino(player->mino);
	mino_checker->current_col--;
	if (is_game_on(mino_checker, player->table->table_array))
		player->mino->current_col--;
	free_mino(mino_checker);
}

void	move_mino_right(t_player *player)
{
	t_mino	*mino_checker;

	mino_checker = duplicate_mino(player->mino);
	mino_checker->current_col++;
	if (is_game_on(mino_checker, player->table->table_array))
		player->mino->current_col++;
	free_mino(mino_checker);
}
