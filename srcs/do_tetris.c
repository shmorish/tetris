# include "tetris.h"

void do_tetris(t_tetris *tetris)
{
	int	key_input;

	while (1)
	{
		key_input = getch();
		if (key_input != ERR)
		{
			dup_mino_data(tetris);
			if (key_input == KEY_UP)
				rotate_tetris(tetris);
			else if (key_input == KEY_DOWN)
				move_down(tetris);
			else if (key_input == KEY_LEFT)
				move_mino(tetris, -1);
			else if (key_input == KEY_RIGHT)
				move_mino(tetris, 1);
			print_table(GAME_ON, tetris->table, tetris->score);
		}
		if (time_elapses(tetris))
		{
			move_down(tetris);
			print_table(GAME_ON, tetris->table, tetris->score);
			update_exec_time();
		}
		// if (is_gameover(tetris))
		break ;
	}
}