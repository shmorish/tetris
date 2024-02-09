#include "tetris.h"

int decrease = 1000;

int isGameActive(t_mino *shape, t_player *player)
{
	char **array = shape->mino_array;
	int i, j;
	for (i = 0; i < shape->mino_size; i++){
		for (j = 0; j < shape->mino_size; j++){
			if ((shape->current_col + j < 0 || shape->current_col + j >= COLUMNS || shape->current_row + i >= ROWS))
			{
				if(array[i][j])
					return false;
			}
			else if (player->table->table_array[shape->current_row + i][shape->current_col + j] && array[i][j])
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
	t_mino		*current;

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
	initscr();
	timeout(1);
	srand(time(NULL));



	gettimeofday(&before_now, NULL);
	generate_mino(player);
	current = duplicatet_mino(*player->mino);
	if(!isGameActive(current, player))
		player->table->is_game_on = false;
	print_game(current, player);
	int c;
	while(player->table->is_game_on)
	{
		if ((c = getch()) != ERR)
		{
			t_mino *tmp = duplicatet_mino(*current);
			switch(c)
			{
				case 's':
					tmp->current_row++;  //move down
					if(isGameActive(tmp, player))
						current->current_row++;
					else
					{
						int i, j;
						for(i = 0; i < current->mino_size ;i++){
							for(j = 0; j < current->mino_size ; j++){
								if(current->mino_array[i][j])
									player->table->table_array[current->current_row+i][current->current_col+j] = current->mino_array[i][j];
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
						destruct_mino_struct(current);
						generate_new_mino(player);
						current = duplicatet_mino(*player->mino);
						if(!isGameActive(current, player))
							player->table->is_game_on = false;
					}
					break;
				case 'd': //move right
					tmp->current_col++;
					if(isGameActive(tmp, player))
						current->current_col++;
					break;
				case 'a': //move left
					tmp->current_col--;
					if(isGameActive(tmp, player))
						current->current_col--;
					break;
				case 'w': //rotate
					rotate_Tetromino(tmp);
					if(isGameActive(tmp, player))
						rotate_Tetromino(current);
					break;
			}
			destruct_mino_struct(tmp);
			print_game(current, player);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate(player))
		{
			t_mino *tmp = duplicatet_mino(*current);
			switch('s')
			{
				case 's':
					tmp->current_row++;
					if(isGameActive(tmp, player))
						current->current_row++;
					else
					{
						int i, j;
						for(i = 0; i < current->mino_size ;i++){
							for(j = 0; j < current->mino_size ; j++){
								if(current->mino_array[i][j])
									player->table->table_array[current->current_row+i][current->current_col+j] = current->mino_array[i][j];
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
						destruct_mino_struct(current);
						generate_new_mino(player);
						current = duplicatet_mino(*player->mino);
						if(!isGameActive(current, player))
							player->table->is_game_on = false;
					}
					break;
				case 'd':
					tmp->current_col++;
					if(isGameActive(tmp, player))
						current->current_col++;
					break;
				case 'a':
					tmp->current_col--;
					if(isGameActive(tmp, player))
						current->current_col--;
					break;
				case 'w':
					rotate_Tetromino(tmp);
					if(isGameActive(tmp, player))
						rotate_Tetromino(current);
					break;
			}
			destruct_mino_struct(tmp);
			print_game(current, player);
			gettimeofday(&before_now, NULL);
		}
	}
	destruct_mino_struct(current);
	endwin();
	print_game_over(player);
	destruct_player_struct(player);
	return 0;
}

