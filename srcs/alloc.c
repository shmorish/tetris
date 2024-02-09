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

t_mino *duplicate_mino(t_mino mino)
{
	t_mino *new_mino = (t_mino *)xmalloc(sizeof(t_mino));

	new_mino->mino_size = mino.mino_size;
	new_mino->mino_array = (char **)xmalloc(sizeof(char *) * (new_mino->mino_size + 1));
	for (int i = 0; i < new_mino->mino_size; i++)
	{
		new_mino->mino_array[i] = (char *)xmalloc(sizeof(char) * (new_mino->mino_size + 1));
		memcpy(new_mino->mino_array[i], mino.mino_array[i], new_mino->mino_size);
	}
	new_mino->current_row = mino.current_row;
	new_mino->current_col = mino.current_col;
	return new_mino;
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
