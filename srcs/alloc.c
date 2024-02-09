#include "tetris.h"



void *xmalloc(size_t size)
{
	void *p = malloc(size);
	if (p == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

t_mino *duplicatet_mino(t_mino shape)
{
    t_mino *new_shape = (t_mino *)xmalloc(sizeof(t_mino));
    char **copyshape = shape.mino_array;

    new_shape->mino_size = shape.mino_size;
    new_shape->mino_array = (char **)xmalloc(new_shape->mino_size * sizeof(char *));
    for (int i = 0; i < new_shape->mino_size; i++) {
        new_shape->mino_array[i] = (char *)xmalloc(new_shape->mino_size * sizeof(char));
        memcpy(new_shape->mino_array[i], copyshape[i], new_shape->mino_size);
    }
	new_shape->current_row = shape.current_row;
	new_shape->current_col = shape.current_col;
    return new_shape;
}

void free_array(t_mino *shape)
{
    int i;
    for(i = 0; i < shape->mino_size; i++){
		free(shape->mino_array[i]);
        shape->mino_array[i] = NULL;
    }
    free(shape->mino_array);
    shape->mino_array = NULL;
    free(shape);
    shape = NULL;
}
