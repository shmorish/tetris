#include "tetris.h"

char	*memdup(const char *src, int size)
{
	char	*dest;

	dest = (char *)xcalloc(sizeof(char), size + 1);
	memcpy(dest, src, size);
	return (dest);
}

void	*xcalloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = calloc(count, size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
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

char	**init_table(void)
{
	char	**table;

	table = (char **)xcalloc(sizeof(char *), ROWS + 1);
	for (int i = 0; i < ROWS; i++)
		table[i] = (char *)xcalloc(sizeof(char), COLUMNS + 1);
	table[ROWS] = NULL;
	return table;
}

char	**table_dup(char **table)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char **)xcalloc(sizeof(char *), ROWS + 1);
	while (i < ROWS)
	{
		tmp[i] = memdup(table[i], COLUMNS);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}