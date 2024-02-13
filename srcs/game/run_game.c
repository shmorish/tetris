#include "game.h"

// 一定時間が経過したら落下中のミノを一段下に落とす
static void	time_elapse_event(t_player *player)
{
	if (time_elapsed(player->table))
	{
		move_mino_down(player);
		update_exec_time();
	}
}

void	run_game(t_player *player)
{
	generate_mino(player->mino);
	while (is_game_on(player->mino, player->table->table_array))
	{
		render_table(player);
		key_events(player);
		time_elapse_event(player);
	}
}
