# include "tetris.h"

void do_tetris(t_tetris *tetris)
{
	int	key_input;

	generate_mino(tetris);
	print_table(GAME_ON, tetris, tetris->score);
	while (possible_to_move(tetris, tetris->current_row, tetris->current_col))
	{
		key_input = getch();
		if (key_input != ERR)
		{
			dup_mino_data(tetris);
			if (key_input == W_KEY)
				rotate_mino(tetris);
			else if (key_input == S_KEY)
				move_down(tetris);
			else if (key_input == A_KEY)
				move_mino(tetris, -1);
			else if (key_input == D_KEY)
				move_mino(tetris, 1);
			print_table(GAME_ON, tetris, tetris->score);
		}
		if (time_elapses(tetris))
		{
			move_down(tetris);
			print_table(GAME_ON, tetris, tetris->score);
			update_exec_time();
		}
	}
}