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

int main()
{
	t_player	*player;

	/* init_struct */
	player = init_struct();

	/* init_game */
	init_game();

	generate_mino(player);
	if(!isGameActive(player->mino, player))
		player->table->is_game_on = false;
	print_game(player->mino, player);
	while (player->table->is_game_on)
	{
		print_game(player->mino, player);
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
