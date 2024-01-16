#include "tetris.h"

char Table[ROWS][COLUMNS] = {0};
bool GameOn = true;
suseconds_t timer = 400000;
int decrease = 1000;


int isGameActive(Struct *shape){
	char **array = shape->array;
	int i, j;
	for(i = 0; i < shape->width; i++){
		for(j = 0; j < shape->width; j++){
			if((shape->col + j < 0 || shape->col + j >= COLUMNS || shape->row + i >= ROWS)){
				if(array[i][j])
					return false;
			}
			else if(Table[shape->row + i][shape->col + j] && array[i][j])
				return false;
		}
	}
	return true;
}

int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}

int main() {
    srand(time(0));
	Struct *current;
    int final = 0;
    int c;
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	Struct *new_shape = generateTetromino();
	current = new_shape;
	if(!isGameActive(current)){
		GameOn = false;
	}
    print_game(final, current, Table);
	while(GameOn){
		if ((c = getch()) != ERR) {
			Struct *temp = duplicateStruct(*current);
			switch(c){
				case 's':
					temp->row++;  //move down
					if(isGameActive(temp))
						current->row++;
					else {
						int i, j;
						for(i = 0; i < current->width ;i++){
							for(j = 0; j < current->width ; j++){
								if(current->array[i][j])
									Table[current->row+i][current->col+j] = current->array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<ROWS;n++){
							sum = 0;
							for(m=0;m< COLUMNS;m++) {
								sum+=Table[n][m];
							}
							if(sum==COLUMNS){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<COLUMNS;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<COLUMNS;l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						final += 100*count;
						Struct *new_shape = generateTetromino();
						free_array(current);
						current = new_shape;
						if(!isGameActive(current)){
							GameOn = false;
						}
					}
					break;
				case 'd': //move right
					temp->col++;
					if(isGameActive(temp))
						current->col++;
					break;
				case 'a': //move left
					temp->col--;
					if(isGameActive(temp))
						current->col--;
					break;
				case 'w': //rotate
					rotate_Tetromino(temp);
					if(isGameActive(temp))
						rotate_Tetromino(current);
					break;
			}
			free_array(temp);
			print_game(final, current, Table);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			Struct *temp = duplicateStruct(*current);
			switch('s'){
				case 's':
					temp->row++;
					if(isGameActive(temp))
						current->row++;
					else {
						int i, j;
						for(i = 0; i < current->width ;i++){
							for(j = 0; j < current->width ; j++){
								if(current->array[i][j])
									Table[current->row+i][current->col+j] = current->array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<ROWS;n++){
							sum = 0;
							for(m=0;m< COLUMNS;m++) {
								sum+=Table[n][m];
							}
							if(sum==COLUMNS){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<COLUMNS;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<COLUMNS;l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						Struct *new_shape = generateTetromino();
						free_array(current);
						current = new_shape;
						if(!isGameActive(current)){
							GameOn = false;
						}
					}
					break;
				case 'd':
					temp->col++;
					if(isGameActive(temp))
						current->col++;
					break;
				case 'a':
					temp->col--;
					if(isGameActive(temp))
						current->col--;
					break;
				case 'w':
					rotate_Tetromino(temp);
					if(isGameActive(temp))
						rotate_Tetromino(current);
					break;
			}
			free_array(temp);
			print_game(final, current, Table);
			gettimeofday(&before_now, NULL);
		}
	}
	free_array(current);
	endwin();
	print_game_over(final, Table);
    return 0;
}

