#include "tetris.h"

static char	**init_table(void);

t_tetris *init_struct(void)
{
	t_tetris *tetris;

	tetris = (t_tetris *)xcalloc(sizeof(t_tetris), 1);
	tetris->mino_data = NULL;
	tetris->tmp_mino_data = NULL;

	tetris->mino_size = 0;
	tetris->current_row = 0;
	tetris->current_col = 0;
	tetris->time_to_execute = 400000;
	tetris->table = init_table();
	// tetris->tmp_table = init_table();
	tetris->score = 0;
	return	tetris;
}

void	free_array(char **str)
{
	if (!str)
		return ;
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
	free_array(tetris->mino_data);
	free_array(tetris->tmp_mino_data);
	free_array(tetris->table);
	free_array(tetris->tmp_table);
	free(tetris);
	tetris = NULL;
}

void	dup_mino_data(t_tetris *tetris)
{
	int i;

	i = 0;
	free_array(tetris->tmp_mino_data);
	tetris->tmp_mino_data = (char **)xcalloc(sizeof(char *), tetris->mino_size + 1);
	while (i < tetris->mino_size)
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
	tetris->tmp_mino_data[i] = NULL;
}

void	*xcalloc(size_t count, size_t size)
{
	void *ptr;

	ptr = calloc(count, size);
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

	table = (char **)xcalloc(sizeof(char *), ROWS + 1);
	i = 0;
	while (i < ROWS)
	{
		table[i] = (char *)xcalloc(sizeof(char), COLUMNS + 1);
		i++;
	}
	table[i] = NULL;
	return (table);
}
