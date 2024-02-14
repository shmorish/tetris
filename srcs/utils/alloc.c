#include "utils.h"

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	return (p);
}

void	*memdup(const void *src, size_t size)
{
	char	*dest;

	dest = (void *)xmalloc(size + 1);
	memcpy(dest, src, size);
	return (dest);
}

t_player	*init_player(void)
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
	return (player);
}

char	**init_table(void)
{
	char	**table;

	table = (char **)xmalloc(sizeof(char *) * (ROWS + 1));
	for (int i = 0; i < ROWS; i++)
		table[i] = (char *)xmalloc(sizeof(char) * (COLUMNS + 1));
	table[ROWS] = NULL;
	for (int row_i = 0; row_i < ROWS; row_i++)
		for (int col_i = 0; col_i < COLUMNS; col_i++)
			table[row_i][col_i] = 0;
	return (table);
}

t_mino *duplicate_mino(t_mino *mino)
{
	t_mino *new_mino;

	new_mino = (t_mino *)xmalloc(sizeof(t_mino));
	new_mino->mino_size = mino->mino_size;
	new_mino->current_row = mino->current_row;
	new_mino->current_col = mino->current_col;
	new_mino->mino_array = (char **)xmalloc(sizeof(char *) * (new_mino->mino_size + 1));
	for (int i = 0; i < new_mino->mino_size; i++)
		new_mino->mino_array[i] = memdup(mino->mino_array[i], new_mino->mino_size);
	new_mino->mino_array[mino->mino_size] = NULL;
	return (new_mino);
}
