#include "tetris.h"

int can_mino_move(t_mino *check_mino, char **table)
{
	for (int i = 0; i < check_mino->mino_size; i++) {
		for (int j = 0; j < check_mino->mino_size; j++) {
			if ((check_mino->current_col + j < 0 || check_mino->current_col + j >= COLUMNS || check_mino->current_row + i >= ROWS))
			{
				if(check_mino->mino_array[i][j])
					return false;
			}
			else if (table[check_mino->current_row + i][check_mino->current_col + j] && check_mino->mino_array[i][j])
				return false;
		}
	}
	return true;
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
