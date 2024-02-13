#include "tetris.h"

int	main(void)
{
	t_player	*player;

	player = init_player();
	init_game();
	run_game(player);
	end_game(player);
	return (0);
}

#ifdef DEBUG

__attribute__((destructor)) void end(void)
{
	system("leaks -q tetris > /dev/stderr");
}

#endif
