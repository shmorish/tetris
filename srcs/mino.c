#include "tetris.h"
# define MINO_TYPES 7

const Struct Tetromino[MINO_TYPES] = {
    {
		// S mino
		// green
        .array = (char *[]) {
            (char []){0, 1, 1},
            (char []){1, 1, 0},
            (char []){0, 0, 0}
        },
        .size = 3
    },
	{
		// Z mino
		// red
		.array = (char *[]) {
			(char []){1, 1, 0},
			(char []){0, 1, 1},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// T mino
		// purple
		.array = (char *[]) {
			(char []){0, 1, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// J mino
		// blue
		.array = (char *[]) {
			(char []){1, 0, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// L mino
		// orange
		.array = (char *[]) {
			(char []){0, 0, 1},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// O mino
		// yellow
		.array = (char *[]) {
			(char []){1, 1},
			(char []){1, 1}
		},
		.size = 2
	},
	{
		// I mino
		// cyan
		.array = (char *[]) {
			(char []){0, 0, 0, 0},
			(char []){1, 1, 1, 1},
			(char []){0, 0, 0, 0},
			(char []){0, 0, 0, 0}
		},
		.size = 4
	}
};

/* generate_mino();を用いるため不要 */
Struct *generateTetromino()
{
	// Struct shape = Tetromino[rand() % MINO_TYPES];
	Struct shape = Tetromino[6];
	shape.col = rand() % (COLUMNS - shape.size + 1);
	shape.row = 0;
	return duplicateStruct(shape);
}

char	*memdup(const char *src, int size)
{
	char	*dest;

	dest = (char *)xcalloc(sizeof(char), size + 1);
	memcpy(dest, src, size);
	return (dest);
}

char **mino_dup(Struct src_mino)
{
	char	**dest_mino;

	dest_mino = (char **)xmalloc(sizeof(char *) * (src_mino.size + 1));
	for (int i = 0; i < src_mino.size; i++)
		dest_mino[i] = memdup(src_mino.array[i], src_mino.size);
	dest_mino[src_mino.size] = NULL;
	return (dest_mino);
}

void	generate_mino(t_player *player)
{
	int mino_index;

	mino_index = rand() % MINO_TYPES;
	player->mino->mino_size = Tetromino[mino_index].size;
	player->mino->mino_array = mino_dup(Tetromino[mino_index]);
	player->mino->current_row = 0;
	player->mino->current_col = rand() % (COLUMNS - player->mino->mino_size + 1);
}

void rotate_Tetromino(Struct *shape)
{
	Struct *temp = duplicateStruct(*shape);
	int k, size;
	size = shape->size;
	for(int i = 0; i < size ; i++){
		for(int j = 0, k = size - 1; j < size; j++, k--){
				shape->array[i][j] = temp->array[k][i];
		}
	}
	free_array(temp);
}
