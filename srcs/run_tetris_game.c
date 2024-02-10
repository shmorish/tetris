#include "tetris.h"
#define W_KEY 'w'
#define A_KEY 'a'
#define S_KEY 's'
#define D_KEY 'd'

void	rotate_mino(t_player *player)
{
	t_mino	*movable_check_mino;

	movable_check_mino = duplicate_mino(*player->mino);
	rotate_Tetromino(movable_check_mino);
	if (isGameActive(movable_check_mino, player))
		rotate_Tetromino(player->mino);
	destroy_struct(movable_check_mino);
}

void	move_mino_down(t_player *player)
{
	t_mino	*movable_check_mino;

	movable_check_mino = duplicate_mino(*player->mino);
	movable_check_mino->current_row++;
	if (isGameActive(movable_check_mino, player))
		player->mino->current_row++;
	else
	{
		put_mino_data_to_table(player->table, (const char **)player->mino->mino_array, \
			player->mino->current_row, player->mino->current_col, player->mino->mino_size);
		player->table->score += clear_mino(player);
		generate_new_mino(player);
		if (can_mino_move(player) == false)
			player->table->is_game_on = GAME_OVER;
	}
	destroy_struct(movable_check_mino);
}

void	key_events(t_player *player)
{
	int	key_input;

	key_input = getch();
	if (key_input != ERR)
	{
		if (key_input == W_KEY)
			rotate_mino(player);
		else if (key_input == S_KEY)
			move_mino_down(player);
		else if (key_input == A_KEY)
			move_mino_left(player);
		else if (key_input == D_KEY)
			move_mino_right(player);
	}
}
