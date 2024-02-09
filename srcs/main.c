#include "tetris.h"

int decrease = 1000;


int isGameActive(t_mino *shape, t_player *player)
{
	char **array = shape->mino_array;
	int i, j;
	for(i = 0; i < shape->mino_size; i++){
		for(j = 0; j < shape->mino_size; j++){
			if((shape->current_col + j < 0 || shape->current_col + j >= COLUMNS || shape->current_row + i >= ROWS)){
				if(array[i][j])
					return false;
			}
			else if(player->table->table_array[shape->current_row + i][shape->current_col + j] && array[i][j])
				return false;
		}
	}
	return true;
}

int hasToUpdate(t_player *player)
{
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > player->table->time_to_execute;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}

char	**init_table(void)
{
	char	**table;

	table = (char **)xmalloc(sizeof(char *) * (ROWS + 1));
	for (int i = 0; i < ROWS; i++)
		table[i] = (char *)xmalloc(sizeof(char) * (COLUMNS + 1));
	table[ROWS] = NULL;
	return table;
}

int main() {
	t_player	*player;

	srand(time(0));
	t_mino *current;
	// t_mino *current;

	/* init_struct */
	player = (t_player *)xmalloc(sizeof(t_player));
	player->mino->mino_array = NULL;
	player->mino->mino_size = 0;
	player->mino->current_row = 0;
	player->mino->current_col = 0;
	player->table->time_to_execute = INITIAL_TIME_TO_EXECVE_ms;
	player->table->table_array = init_table();
	player->table->score = 0;
	player->table->is_game_on = true;

    int c;
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	// t_mino *new_shape = generateTetromino();
	generate_mino(player);
	current = player->mino;
	if(!isGameActive(current, player))
		player->table->is_game_on = false;
    print_game(current, player);
	while(player->table->is_game_on)
	{
		if ((c = getch()) != ERR) {
			t_mino *temp = duplicatet_mino(*current);
			switch(c){
				case 's':
					temp->current_row++;  //move down
					if(isGameActive(temp, player))
						current->current_row++;
					else {
						int i, j;
						for(i = 0; i < current->mino_size ;i++){
							for(j = 0; j < current->mino_size ; j++){
								if(current->mino_array[i][j])
									player->table->table_array[current->current_row+i][current->current_col+j] = current->mino_array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<ROWS;n++){
							sum = 0;
							for(m=0;m< COLUMNS;m++) {
								sum += player->table->table_array[n][m];
							}
							if(sum==COLUMNS){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<COLUMNS;l++)
										player->table->table_array[k][l] = player->table->table_array[k-1][l];
								for(l=0;l<COLUMNS;l++)
									player->table->table_array[k][l]=0;
								player->table->time_to_execute -=decrease--;
							}
						}
						player->table->score += 100*count;
						t_mino *new_shape = generateTetromino();
						free_array(current);
						current = new_shape;
						if(!isGameActive(current, player))
							player->table->is_game_on = false;
					}
					break;
				case 'd': //move right
					temp->current_col++;
					if(isGameActive(temp, player))
						current->current_col++;
					break;
				case 'a': //move left
					temp->current_col--;
					if(isGameActive(temp, player))
						current->current_col--;
					break;
				case 'w': //rotate
					rotate_Tetromino(temp);
					if(isGameActive(temp, player))
						rotate_Tetromino(current);
					break;
			}
			free_array(temp);
			print_game(current, player);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate(player))
		{
			t_mino *temp = duplicatet_mino(*current);
			switch('s'){
				case 's':
					temp->current_row++;
					if(isGameActive(temp, player))
						current->current_row++;
					else {
						int i, j;
						for(i = 0; i < current->mino_size ;i++){
							for(j = 0; j < current->mino_size ; j++){
								if(current->mino_array[i][j])
									player->table->table_array[current->current_row+i][current->current_col+j] = current->mino_array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<ROWS;n++){
							sum = 0;
							for(m=0;m< COLUMNS;m++) {
								sum += player->table->table_array[n][m];
							}
							if(sum==COLUMNS){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<COLUMNS;l++)
										player->table->table_array[k][l] = player->table->table_array[k-1][l];
								for(l=0;l<COLUMNS;l++)
									player->table->table_array[k][l] = 0;
								player->table->time_to_execute -=decrease--;
							}
						}
						t_mino *new_shape = generateTetromino();
						free_array(current);
						current = new_shape;
						if(!isGameActive(current, player))
							player->table->is_game_on = false;
					}
					break;
				case 'd':
					temp->current_col++;
					if(isGameActive(temp, player))
						current->current_col++;
					break;
				case 'a':
					temp->current_col--;
					if(isGameActive(temp, player))
						current->current_col--;
					break;
				case 'w':
					rotate_Tetromino(temp);
					if(isGameActive(temp, player))
						rotate_Tetromino(current);
					break;
			}
			free_array(temp);
			print_game(current, player);
			gettimeofday(&before_now, NULL);
		}
	}
	free_array(current);
	endwin();
	print_game_over(player);
    return 0;
}

