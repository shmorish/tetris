#include "tetris.h"

#define W_KEY 'w'
#define A_KEY 'a'
#define S_KEY 's'
#define D_KEY 'd'

void	put_mino_data_to_table(t_mino *mino, char **table)
{
	for (int y = 0; y < mino->mino_size; y++)
		for (int x = 0; x < mino->mino_size; x++)
			if (mino->mino_array[y][x] != 0)
				table[mino->current_row + y][mino->current_col + x] = mino->mino_array[y][x];
}

static void	key_events(t_player *player)
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

static void	time_elapse_event(t_player *player)
{
	if (time_elapsed(player->table))
	{
		move_mino_down(player);
		update_exec_time();
	}
}

void	run_tetris_game(t_player *player)
{
	/* init_struct */
	player = init_struct();

	/* init_game */
	init_game();

	generate_mino(player->mino);
	if(!can_mino_move(player->mino, player->table->table_array))
		player->table->is_game_on = false;
	while (player->table->is_game_on)
	{
		print_output_according_to_fps(player);
		key_events(player);
		time_elapse_event(player);
	}
}
