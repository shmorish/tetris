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

Struct *duplicateStruct(Struct shape)
{
    Struct *new_shape = (Struct *)xmalloc(sizeof(Struct));
    char **copyshape = shape.array;

    new_shape->size = shape.size;
    new_shape->array = (char **)xmalloc(new_shape->size * sizeof(char *));
    for (int i = 0; i < new_shape->size; i++) {
        new_shape->array[i] = (char *)xmalloc(new_shape->size * sizeof(char));
        memcpy(new_shape->array[i], copyshape[i], new_shape->size);
    }
	new_shape->row = shape.row;
	new_shape->col = shape.col;
    return new_shape;
}

void free_array(Struct *shape)
{
    int i;
    for(i = 0; i < shape->size; i++){
		free(shape->array[i]);
        shape->array[i] = NULL;
    }
    free(shape->array);
    shape->array = NULL;
    free(shape);
    shape = NULL;
}
