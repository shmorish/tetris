#include "tetris.h"

t_player	*init_struct(void)
{
	t_player	*player;

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
	return (player);
}

void	destruct_table_struct(t_table *table)
{
	free_array(table->table_array);
	free(table);
	table = NULL;
}

void	destruct_mino_struct(t_mino *mino)
{
	free_array(mino->mino_array);
	free(mino);
	mino = NULL;
}

void	destruct_player_struct(t_player *player)
{
	destruct_table_struct(player->table);
	destruct_mino_struct(player->mino);
	free(player);
	player = NULL;
}
