#include "tetris.h"

t_tetris *init_tetris(void)
{
	t_tetris *tetris;

	tetris->map = init_map();

	return	tetris;
}

int main(void)
{
	t_tetris *tetris;
	int final_score;

	/* 初期化する
	・開始時間を取得する
	・空盤面を生成する
	*/
	tetris = init_tetris();

	/* ゲームを実行する
	繰り返す
	{
		・マップを表示させる
		・入力（WASD）を受け付ける
		・入力をもとにコマンドを実行する
		・時間経過でものを落とす
	}
	*/
	final_score = do_tetris(tetris);

	/* ゲームを終了する */
	end_tetris(tetris, final_score);
}
