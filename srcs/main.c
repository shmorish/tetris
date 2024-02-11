#include "tetris.h"

int isGameActive(t_mino *movable_check_mino, t_player *player)
{
	int i, j;
	for (i = 0; i < movable_check_mino->mino_size; i++){
		for (j = 0; j < movable_check_mino->mino_size; j++){
			if ((movable_check_mino->current_col + j < 0 || movable_check_mino->current_col + j >= COLUMNS || movable_check_mino->current_row + i >= ROWS))
			{
				if(movable_check_mino->mino_array[i][j])
					return false;
			}
			else if (player->table->table_array[movable_check_mino->current_row + i][movable_check_mino->current_col + j] && movable_check_mino->mino_array[i][j])
				return false;
		}
	}
	return true;
}

void	run_tetris_game(t_player *player)
{
	generate_mino(player);
	if (!isGameActive(player->mino, player))
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
