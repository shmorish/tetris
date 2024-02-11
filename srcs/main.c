#include "tetris.h"

void	run_tetris_game(t_player *player)
{
	/* init_struct */
	player = init_struct();

	/* init_game */
	init_game();

	generate_mino(player->mino);
	if (can_mino_move(player->mino, player->table->table_array) == false)
		player->table->is_game_on = false;
	while (player->table->is_game_on)
	{
		print_output_according_to_fps(player);
		key_events(player);
		time_elapse_event(player);
	}
}

int	main(void)
{
	t_player	*player;

	player = init_struct();
	init_game();
	run_tetris_game(player);
	end_game(player);
	destruct_player_struct(player);
	return (0);
}

#ifdef DEBUG

__attribute__((destructor)) void end(void)
{
	system("leaks -q tetris > /dev/stderr");
}

#endif
