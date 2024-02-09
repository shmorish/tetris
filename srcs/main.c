#include "tetris.h"

int decrease = 1000;


int isGameActive(Struct *shape, t_player *player)
{
	char **array = shape->array;
	int i, j;
	for(i = 0; i < shape->width; i++){
		for(j = 0; j < shape->width; j++){
			if((shape->col + j < 0 || shape->col + j >= COLUMNS || shape->row + i >= ROWS)){
				if(array[i][j])
					return false;
			}
			else if(player->table->table_array[shape->row + i][shape->col + j] && array[i][j])
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

	player = (t_player *)xmalloc(sizeof(t_player));
	srand(time(0));
	Struct *current;

	/* init_struct */
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
	Struct *new_shape = generateTetromino();
	current = new_shape;
	if(!isGameActive(current, player))
		player->table->is_game_on = false;
    print_game(current, player);
	while(player->table->is_game_on)
	{
		if ((c = getch()) != ERR) {
			Struct *temp = duplicateStruct(*current);
			switch(c){
				case 's':
					temp->row++;  //move down
					if(isGameActive(temp, player))
						current->row++;
					else {
						int i, j;
						for(i = 0; i < current->width ;i++){
							for(j = 0; j < current->width ; j++){
								if(current->array[i][j])
									player->table->table_array[current->row+i][current->col+j] = current->array[i][j];
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
						Struct *new_shape = generateTetromino();
						free_array(current);
						current = new_shape;
						if(!isGameActive(current, player))
							player->table->is_game_on = false;
					}
					break;
				case 'd': //move right
					temp->col++;
					if(isGameActive(temp, player))
						current->col++;
					break;
				case 'a': //move left
					temp->col--;
					if(isGameActive(temp, player))
						current->col--;
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
			Struct *temp = duplicateStruct(*current);
			switch('s'){
				case 's':
					temp->row++;
					if(isGameActive(temp, player))
						current->row++;
					else {
						int i, j;
						for(i = 0; i < current->width ;i++){
							for(j = 0; j < current->width ; j++){
								if(current->array[i][j])
									player->table->table_array[current->row+i][current->col+j] = current->array[i][j];
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
						Struct *new_shape = generateTetromino();
						free_array(current);
						current = new_shape;
						if(!isGameActive(current, player))
							player->table->is_game_on = false;
					}
					break;
				case 'd':
					temp->col++;
					if(isGameActive(temp, player))
						current->col++;
					break;
				case 'a':
					temp->col--;
					if(isGameActive(temp, player))
						current->col--;
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

