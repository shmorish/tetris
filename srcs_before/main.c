#include "tetris_before.h"

char Table[ROWS][COLUMNS] = {0};	//	盤面
bool GameOn = true;			//	ゲームオーバーかどうか（ゲームを終了するかどうか）を範囲するためのフラグ
suseconds_t timer = 400000;	//	盤面の更新にかかる時間（変える予定がないから定数で良いのでは？）
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

// 盤面を更新する時間が経ったか
int hasToUpdate()
{
	return ((suseconds_t)(now.tv_sec * 1000000 + now.tv_usec) - ((suseconds_t)before_now.tv_sec * 1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	// time = 1;
	timeout(1);
}

int main() {
    /* 初期化する */

	// 乱数生成のタネを作る
	srand(time(0));
	// 構造体をつくる
	Struct *current;
    // ファイナルスコアの変数を初期化する
	int final = 0;
    // ウィンドウを初期化する
	initscr();
	// 現在時刻を取得する
	gettimeofday(&before_now, NULL);
	// キー入力待ち時間（普通は 1 ms 以上）を設定する．
	set_timeout(1);


	/* ゲームを実行する */
	// ミノを生成する
	Struct *new_shape = generateTetromino();
	current = new_shape;

	// ゲームオーバーでないかを確認する
	if(!isGameActive(current))
		GameOn = false;
    // 空盤面を生成する
	print_game(final, current, Table);

	// 現在時刻を取得する
	gettimeofday(&now, NULL);
	// 入力文字の変数を宣言する（━▶︎ゲームを実行する）
	int c;
	while(GameOn)
	{
		// 入力された文字列が正常である，または変更が必要
		if ((c = getch()) != ERR || hasToUpdate())
		{
			Struct *temp = duplicateStruct(*current);
			switch(c)
			{
				case 's':
					temp->row++;  //move down
					if(isGameActive(temp))
						current->row++;
					else
					{
						for(int i = 0; i < current->width ;i++){
							for(int j = 0; j < current->width ; j++)
							{
								if(current->array[i][j])
									Table[current->row + i][current->col + j] = current->array[i][j];
							}
						}
						int sum, count = 0;
						for(int n = 0; n < ROWS; n++)
						{
							sum = 0;
							for(int m = 0; m < COLUMNS; m++)
								sum += Table[n][m];
							if(sum == COLUMNS)
							{
								count++;
								int l, k;
								for(k = n; k >= 1; k--)
									for(l = 0; l < COLUMNS; l++)
										Table[k][l] = Table[k - 1][l];
								for(l = 0; l < COLUMNS; l++)
									Table[k][l] = 0;
								timer -= decrease--;
							}
						}
						final += 1500 * count;
						Struct *new_shape = generateTetromino();
						free_array(current);
						current = new_shape;
						if(!isGameActive(current))
							GameOn = false;
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
			gettimeofday(&before_now, NULL);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate())
		{
			Struct *temp = duplicateStruct(*current);
			switch('s')
			{
				case 's':
					temp->row++;
					if(isGameActive(temp))
						current->row++;
					else
					{
						for(int i = 0; i < current->width; i++){
							for(int j = 0; j < current->width; j++){
								if(current->array[i][j])
									Table[current->row + i][current->col + j] = current->array[i][j];
							}
						}
						int sum, count = 0;
						for(int n = 0; n < ROWS; n++){
							sum = 0;
							for(int m = 0; m < COLUMNS; m++) {
								sum += Table[n][m];
							}
							if(sum == COLUMNS)
							{
								count++;
								int l, k;
								for(k = n; k >= 1; k--)
									for(l = 0; l < COLUMNS; l++)
										Table[k][l] = Table[k - 1][l];
								for(l = 0; l < COLUMNS; l++)
									Table[k][l] = 0;
								timer -= decrease--;
							}
						}
						Struct *new_shape = generateTetromino();
						free_array(current);
						current = new_shape;
						if(!isGameActive(current))
							GameOn = false;
					}
					break;
			}
			free_array(temp);
			print_game(final, current, Table);
			gettimeofday(&before_now, NULL);
		}
	}
	free_array(current);
	endwin(); // ncursesモードを終了
	print_game_over(final, Table);
    return 0;
}

// __attribute__((destructor)) void end(){
// 	system("leaks -q tetris");
// }
