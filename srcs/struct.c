#include "tetris.h"

static char	**init_map(void);

t_tetris *init_struct(void)
{
	t_tetris *tetris;

	tetris = (t_tetris *)xcalloc(sizeof(t_tetris));
	tetris->mino_data = NULL;
	tetris->tmp_mino_data = NULL;

	tetris->mino_size = 0;
	tetris->current_row = 0;
	tetris->current_col = 0;
	tetris->time_to_execute = 400000;
	tetris->table = init_table();
	tetris->tmp_table = init_table();
	tetris->score = 0;
	return	tetris;
}

void	free_array(char **str)
{
	for (int i = 0; str[i] != NULL; i++)
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	destroy_struct(t_tetris *tetris)
{
	int i;

	i = 0;
	free_array(tetris->mino_data);
	free_array(tetris->tmp_mino_data);
	free_array(tetris->table);
	free_array(tetris->tmp_table);
	free(tetris);
	tetris = NULL;
}

void	map_dup(t_tetris *tetris)
{
	int i;

	i = 0;
	while (i < ROWS)
	{
		free(tetris->tmp_mino_data[i]);
		tetris->tmp_mino_data[i] = strdup(tetris->mino_data[i]);
		if (!tetris->tmp_mino_data[i])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	*xcalloc(size_t size)
{
	void *ptr;

	ptr = calloc(1, size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

static char	**init_table(void)
{
	char **table;
	int i;

	table = (char **)xcalloc(sizeof(char *) * (ROWS + 1));
	i = 0;
	while (i < ROWS)
	{
		table[i] = (char *)xcalloc(sizeof(char) * (COLUMNS + 1));
		i++;
	}
	return (table);
}