#include "tetris.h"

static void	passed_time(t_tetris *tetris)
{
	t_tetris	*tmp;

	tmp = dup_mino_data(tetris);
	move_down(tetris, tmp);
	print_table(GAME_ON, tetris, tetris->score);
	update_exec_time();
	destroy_struct(tmp);
}

static void	input_key(t_tetris *tetris)
{
	int			key_input;
	t_tetris	*tmp;

	key_input = getch();
	if (key_input != ERR)
	{
		tmp = dup_mino_data(tetris);
		if (key_input == W_KEY)
			rotate_mino(tetris, tmp);
		else if (key_input == S_KEY)
			move_down(tetris, tmp);
		else if (key_input == A_KEY)
			move_mino(tetris, tmp, -1);
		else if (key_input == D_KEY)
			move_mino(tetris, tmp, 1);
		print_table(GAME_ON, tetris, tetris->score);
		destroy_struct(tmp);
	}
}

void	do_tetris(t_tetris *tetris)
{
	generate_mino(tetris);
	if (!possible_to_move(tetris, tetris->mino_data))
		tetris->game_on = false;
	print_table(GAME_ON, tetris, tetris->score);
	update_exec_time();
	while (tetris->game_on)
	{
		input_key(tetris);
		if (time_elapses(tetris))
			passed_time(tetris);
	}
}
