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

int main()
{
	t_player	*player;

	/* init_struct */
	player = init_struct();

	/* init_game */
	init_game();

	generate_mino(player);
	if(!can_mino_move(player->mino, player))
		player->table->is_game_on = false;
	while (player->table->is_game_on)
	{
		print_output_according_to_fps(player);
		key_events(player);
		time_elapse_event(player);
	}

	/* while文終了後 */
	end_game(player);
	destruct_player_struct(player);
	return 0;
}

#ifdef DEBUG

__attribute__((destructor)) void end(void)
{
	system("leaks -q tetris > /dev/stderr");
}

#endif
