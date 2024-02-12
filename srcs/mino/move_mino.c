#include "mino.h"

static void rotate_tetromino(t_mino *mino)
{
	t_mino *tmp = duplicate_mino(mino);
	int k, size;
	size = mino->mino_size;
	for(int i = 0; i < size ; i++){
		for(int j = 0, k = size - 1; j < size; j++, k--)
				mino->mino_array[i][j] = tmp->mino_array[k][i];
	}
	destruct_mino_struct(tmp);
}

void	rotate_mino(t_player *player)
{
	t_mino	*mino_checker;

	mino_checker = duplicate_mino(player->mino);
	rotate_tetromino(mino_checker);
	if (is_game_on(mino_checker, player->table->table_array))
		rotate_tetromino(player->mino);
	destruct_mino_struct(mino_checker);
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
		if (is_game_on(player->mino, player->table->table_array) == false)
			player->table->is_game_on = GAME_OVER;
	}
	destruct_mino_struct(mino_checker);
}

void	move_mino_left(t_player *player)
{
	t_mino	*mino_checker;

	mino_checker = duplicate_mino(player->mino);
	mino_checker->current_col--;
	if (is_game_on(mino_checker, player->table->table_array))
		player->mino->current_col--;
	destruct_mino_struct(mino_checker);
}

void	move_mino_right(t_player *player)
{
	t_mino	*mino_checker;

	mino_checker = duplicate_mino(player->mino);
	mino_checker->current_col++;
	if (is_game_on(mino_checker, player->table->table_array))
		player->mino->current_col++;
	destruct_mino_struct(mino_checker);
}
