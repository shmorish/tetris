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

void	free_table(t_table *table)
{
	free_array(table->table_array);
	free(table);
	table = NULL;
}

void	free_mino(t_mino *mino)
{
	free_array(mino->mino_array);
	free(mino);
	mino = NULL;
}

void	free_player(t_player *player)
{
	free_table(player->table);
	free_mino(player->mino);
	free(player);
	player = NULL;
}
