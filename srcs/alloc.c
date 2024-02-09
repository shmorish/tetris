#include "tetris.h"

void *xmalloc(size_t size)
{
	void *p = malloc(size);
	if (p == NULL)
    {
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

t_mino *duplicatet_mino(t_mino mino)
{
    t_mino *new_shape = (t_mino *)xmalloc(sizeof(t_mino));
    char **copyshape = mino.mino_array;

    new_shape->mino_size = mino.mino_size;
    new_shape->mino_array = (char **)xmalloc(sizeof(char *) * (new_shape->mino_size + 1));
    for (int i = 0; i < new_shape->mino_size; i++)
	{
        new_shape->mino_array[i] = (char *)xmalloc(sizeof(char) * (new_shape->mino_size + 1));
        memcpy(new_shape->mino_array[i], copyshape[i], new_shape->mino_size);
    }
	new_shape->current_row = mino.current_row;
	new_shape->current_col = mino.current_col;
    return new_shape;
}

void	free_array(char **array)
{
	if (array != NULL || array[0] != NULL)
		return ;
	for (int i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}
