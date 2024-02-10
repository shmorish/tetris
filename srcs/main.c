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

char	**init_table(void)
{
	char	**table;

	table = (char **)xmalloc(sizeof(char *) * (ROWS + 1));
	for (int i = 0; i < ROWS; i++)
		table[i] = (char *)xmalloc(sizeof(char) * (COLUMNS + 1));
	table[ROWS] = NULL;
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			table[i][j] = 0;
	return table;
}

int main()
{
	t_player	*player;

	/* init_struct */
	player = (t_player *)xmalloc(sizeof(t_player));
	player->mino = (t_mino *)xmalloc(sizeof(t_mino));
	player->table = (t_table *)xmalloc(sizeof(t_table));
	player->mino->mino_array = NULL;
	player->mino->mino_size = 0;
	player->mino->current_row = 0;
	player->mino->current_col = 0;
	player->table->time_to_execute = INITIAL_TIME_TO_EXECVE_ms;
	player->table->table_array = init_table();
	player->table->score = 0;
	player->table->is_game_on = true;

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
