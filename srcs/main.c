#include "tetris.h"

// 不要．けす
int time_to_decrease = 1000;

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
	int c;
	while(player->table->is_game_on)
	{
		key_events(player);
		print_game(player->mino, player);

		if (time_elapsed(player->table))
		{
			t_mino *movable_check_mino = duplicate_mino(*player->mino);
			switch('s')
			{
				case 's':
					movable_check_mino->current_row++;
					if(isGameActive(movable_check_mino, player))
						player->mino->current_row++;
					else
					{
						int i, j;
						for(i = 0; i < player->mino->mino_size ;i++){
							for(j = 0; j < player->mino->mino_size ; j++){
								if(player->mino->mino_array[i][j])
									player->table->table_array[player->mino->current_row+i][player->mino->current_col+j] = player->mino->mino_array[i][j];
							}
						}
						int n, m, sum, clear_row_count=0;
						for(n=0;n<ROWS;n++){
							sum = 0;
							for(m=0;m< COLUMNS;m++) {
								sum += player->table->table_array[n][m];
							}
							if(sum==COLUMNS){
								clear_row_count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<COLUMNS;l++)
										player->table->table_array[k][l] = player->table->table_array[k-1][l];
								for(l=0;l<COLUMNS;l++)
									player->table->table_array[k][l] = 0;
								player->table->time_to_execute -=time_to_decrease--;
							}
						}
						player->table->score += clear_row_count * SCORE_PER_BLOCK * COLUMNS;
						generate_new_mino(player);
						if(!isGameActive(player->mino, player))
							player->table->is_game_on = false;
					}
					break;
			}
			destruct_mino_struct(movable_check_mino);
			print_game(player->mino, player);
			update_exec_time();
		}
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
