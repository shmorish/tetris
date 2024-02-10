#include "tetris.h"

/*
	initscr() スクリーンを初期化
	noecho() 入力された文字を表示しない
	curs_set(0) カーソルを非表示
	timeout(1) getch()の待ち時間を1msに設定
	keypad(stdscr, TRUE) キーボードからの入力を受け付ける
	srand(time(NULL)) 乱数の初期化
*/
void	init_game(void)
{
	initscr();
	noecho();
	curs_set(0);
	timeout(1);
	keypad(stdscr, TRUE);
	srand(time(NULL));
	// この処理をあとで入れる。 gettimeofdayの初期化
	// init_time();
}

void	end_game(t_player *player)
{
	endwin();
	print_game_over(player);
	// print_table(GAME_OVER, tetris, tetris->score);
}
