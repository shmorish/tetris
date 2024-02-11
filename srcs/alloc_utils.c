#include "tetris.h"

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

void	*memdup(const void *src, size_t size)
{
	char	*dest;

	dest = (void *)xmalloc(size + 1);
	memcpy(dest, src, size);
	return (dest);
}