# include "tetris.h"

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
	player->table->is_game_on = GAME_ON;
	return (player);
}

char	**init_table(void)
{
	char	**table;

	table = (char **)xmalloc(sizeof(char *) * (ROWS + 1));
	for (int i = 0; i < ROWS; i++)
		table[i] = (char *)xmalloc(sizeof(char) * (COLUMNS + 1));
	table[ROWS] = NULL;
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			table[i][j] = 0;
	return (table);
}

t_mino *duplicate_mino(t_mino *mino)
{
	t_mino *new_mino = (t_mino *)xmalloc(sizeof(t_mino));

	new_mino->mino_size = mino->mino_size;
	new_mino->mino_array = (char **)xmalloc(sizeof(char *) * (new_mino->mino_size + 1));
	for (int i = 0; i < new_mino->mino_size; i++)
	{
		new_mino->mino_array[i] = (char *)xmalloc(sizeof(char) * (new_mino->mino_size + 1));
		memcpy(new_mino->mino_array[i], mino->mino_array[i], new_mino->mino_size);
	}
	new_mino->mino_array[mino->mino_size] = NULL;
	new_mino->current_row = mino->current_row;
	new_mino->current_col = mino->current_col;
	return new_mino;
}

char	**mino_dup(char **mino, int size)
{
	char	**array;

	array = (char **)xmalloc(sizeof(char *) * (size + 1));
	for (int i = 0; i < size; i++)
		array[i] = memdup(mino[i], size);
	array[size] = NULL;
	return (array);
}
