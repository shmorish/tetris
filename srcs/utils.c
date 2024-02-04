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
	char	**tmp;

	tmp = (char **)xcalloc(sizeof(char *), ROWS + 1);
	for (int i = 0; i < ROWS; i++)
		tmp[i] = memdup(table[i], COLUMNS);
	tmp[ROWS] = NULL;
	return (tmp);
}

char	**mino_dup(char **mino, int size)
{
	char	**array;

	array = (char **)xcalloc(sizeof(char *), size + 1);
	for (int i = 0; i < size; i++)
		array[i] = memdup(mino[i], size);
	array[size] = NULL;
	return (array);
}

void	put_mino_data_to_table(char **table, const char **mino_data, int row, int col, int mino_size)
{
    for (int x = 0; x < mino_size; x++)
        for (int y = 0; y < mino_size; y++)
            if (mino_data[x][y] != 0)
                table[row + x][col + y] = mino_data[x][y];
}
