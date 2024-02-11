#include "tetris.h"

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
