#include "tetris.h"

static void	time_elapse_event(t_tetris *tetris)
{
	if (time_elapsed(tetris))
	{
		move_mino_down(tetris);
		update_exec_time();
	}
}

static void	key_events(t_tetris *tetris)
{
	int			key_input;

	key_input = getch();
	if (key_input != ERR)
	{
		if (key_input == W_KEY)
			rotate_mino(tetris);
		else if (key_input == S_KEY)
			move_mino_down(tetris);
		else if (key_input == A_KEY)
			move_mino_left(tetris);
		else if (key_input == D_KEY)
			move_mino_right(tetris);
	}
}

void	do_tetris(t_tetris *tetris)
{
	generate_mino(tetris);
	if (can_mino_move(tetris) == false)
		tetris->game_on = GAME_OVER;
	while (tetris->game_on)
	{
		print_output_according_to_fps(tetris);
		key_events(tetris);
		time_elapse_event(tetris);
	}
}
