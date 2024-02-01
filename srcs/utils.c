# include "tetris.h"

char	*memdup(const char *src, int size)
{
	char	*dest;

	dest = (char *)xcalloc(sizeof(char), size + 1);
	memcpy(dest, src, size);
	return (dest);
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
