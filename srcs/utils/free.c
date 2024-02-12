#include "utils.h"

void	free_array(char **array)
{
	if (array == NULL)
		return ;
	for (int i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void	free_table_struct(t_table *table)
{
	free_array(table->table_array);
	free(table);
	table = NULL;
}

void	free_mino_struct(t_mino *mino)
{
	free_array(mino->mino_array);
	free(mino);
	mino = NULL;
}

void	free_player_struct(t_player *player)
{
	free_table_struct(player->table);
	free_mino_struct(player->mino);
	free(player);
	player = NULL;
}
