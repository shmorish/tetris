#include "tetris.h"

int main(void)
{
	t_tetris	*tetris;

	/* 初期化する
	・開始時間を取得する
	・空盤面を生成する
	*/
	tetris = init_struct();
	init_game();
	/* ゲームを実行する
	繰り返す
	{
		・マップを表示させる
		・入力（WASD）を受け付ける
		・入力をもとにコマンドを実行する
		・時間経過でものを落とす
	}
	*/
	do_tetris(tetris);
	/* ゲームを終了する */
	end_game(tetris);
	destroy_struct(tetris);
	return 0;
}

#ifdef DEBUG

__attribute__((destructor)) void end(void)
{
	system("leaks -q tetris");
}

#endif