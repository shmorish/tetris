#include "game.h"

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
	if (is_game_on(player->mino, player->table->table_array) == false)
		player->table->is_game_on = GAME_OVER;
	while (player->table->is_game_on == GAME_ON)
	{
		render_table(player);
		key_events(player);
		time_elapse_event(player);
	}
}
