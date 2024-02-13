#include "game.h"

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

void	run_game(t_player *player)
{
	generate_mino(player->mino);
	if (is_game_on(player->mino, player->table->table_array) == false)
		player->table->is_game_on = false;
	while (player->table->is_game_on == GAME_ON)
	{
		print_output_according_to_fps(player);
		key_events(player);
		time_elapse_event(player);
	}
}
