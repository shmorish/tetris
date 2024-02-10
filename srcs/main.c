#include "tetris.h"

int decrease = 1000;

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

int hasToUpdate(t_player *player)
{
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > player->table->time_to_execute;
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



	gettimeofday(&before_now, NULL);
	generate_mino(player);
	if(!isGameActive(player->mino, player))
		player->table->is_game_on = false;
	print_game(player->mino, player);
	int c;
	while(player->table->is_game_on)
	{
		if ((c = getch()) != ERR)
		{
			t_mino *movable_check_mino = duplicate_mino(*player->mino);
			switch(c)
			{
				case 's':
					movable_check_mino->current_row++;  //move down
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
									player->table->table_array[k][l]=0;
								player->table->time_to_execute -=decrease--;
							}
						}
						player->table->score += clear_row_count * SCORE_PER_BLOCK * COLUMNS;
						generate_new_mino(player);
						if(!isGameActive(player->mino, player))
							player->table->is_game_on = false;
					}
					break;
				case 'd': //move right
					movable_check_mino->current_col++;
					if(isGameActive(movable_check_mino, player))
						player->mino->current_col++;
					break;
				case 'a': //move left
					movable_check_mino->current_col--;
					if(isGameActive(movable_check_mino, player))
						player->mino->current_col--;
					break;
				case 'w': //rotate
					rotate_Tetromino(movable_check_mino);
					if(isGameActive(movable_check_mino, player))
						rotate_Tetromino(player->mino);
					break;
			}
			destruct_mino_struct(movable_check_mino);
			print_game(player->mino, player);
		}
		gettimeofday(&now, NULL);

		if (hasToUpdate(player))
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
								player->table->time_to_execute -=decrease--;
							}
						}
						player->table->score += clear_row_count * SCORE_PER_BLOCK * COLUMNS;
						generate_new_mino(player);
						if(!isGameActive(player->mino, player))
							player->table->is_game_on = false;
					}
					break;
				case 'd':
					movable_check_mino->current_col++;
					if(isGameActive(movable_check_mino, player))
						player->mino->current_col++;
					break;
				case 'a':
					movable_check_mino->current_col--;
					if(isGameActive(movable_check_mino, player))
						player->mino->current_col--;
					break;
				case 'w':
					rotate_Tetromino(movable_check_mino);
					if(isGameActive(movable_check_mino, player))
						rotate_Tetromino(player->mino);
					break;
			}
			destruct_mino_struct(movable_check_mino);
			print_game(player->mino, player);
			gettimeofday(&before_now, NULL);
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
