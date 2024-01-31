#include "tetris.h"

static void	*xcalloc(size_t size);
static char	**init_map(void);

t_tetris *init_struct(void)
{
	t_tetris *tetris;

	tetris = (t_tetris *)xcalloc(sizeof(t_tetris));
	tetris->map = init_map();
	tetris->tmp_map = init_map();
	tetris->row = 0;
	tetris->col = 0;
	return	tetris;
}

void	destroy_struct(t_tetris *tetris)
{
	int i;

	i = 0;
	while (i < ROWS)
	{
		free(tetris->map[i]);
		tetris->map[i] = NULL;
		i++;
	}
	free(tetris->map);
	tetris->map = NULL;
	free(tetris);
	tetris = NULL;
}

void	map_dup(t_tetris *tetris)
{
	int i;

	i = 0;
	while (i < ROWS)
	{
		free(tetris->tmp_map[i]);
		tetris->tmp_map[i] = strdup(tetris->map[i]);
		if (!tetris->tmp_map[i])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	*xcalloc(size_t size)
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

static char	**init_map(void)
{
	char **map;
	int i;

	map = (char **)xcalloc(sizeof(char *) * (ROWS + 1));
	i = 0;
	while (i < ROWS)
	{
		map[i] = (char *)xcalloc(sizeof(char) * (COLUMNS + 1));
		i++;
	}
	return (map);
}