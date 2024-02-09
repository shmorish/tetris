#include "tetris.h"
# define MINO_TYPES 7

const Struct Tetromino[MINO_TYPES] = {
    {
		// S mino
		// green
        .mino_array = (char *[]) {
            (char []){0, 1, 1},
            (char []){1, 1, 0},
            (char []){0, 0, 0}
        },
        .mino_size = 3
    },
	{
		// Z mino
		// red
		.mino_array = (char *[]) {
			(char []){1, 1, 0},
			(char []){0, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// T mino
		// purple
		.mino_array = (char *[]) {
			(char []){0, 1, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// J mino
		// blue
		.mino_array = (char *[]) {
			(char []){1, 0, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// L mino
		// orange
		.mino_array = (char *[]) {
			(char []){0, 0, 1},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// O mino
		// yellow
		.mino_array = (char *[]) {
			(char []){1, 1},
			(char []){1, 1}
		},
		.mino_size = 2
	},
	{
		// I mino
		// cyan
		.mino_array = (char *[]) {
			(char []){0, 0, 0, 0},
			(char []){1, 1, 1, 1},
			(char []){0, 0, 0, 0},
			(char []){0, 0, 0, 0}
		},
		.mino_size = 4
	}
};

/* generate_mino();を用いるため不要 */
Struct *generateTetromino()
{
	// Struct shape = Tetromino[rand() % MINO_TYPES];
	Struct shape = Tetromino[6];
	shape.current_col = rand() % (COLUMNS - shape.mino_size + 1);
	shape.current_row = 0;
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

	dest_mino = (char **)xmalloc(sizeof(char *) * (src_mino.mino_size + 1));
	for (int i = 0; i < src_mino.mino_size; i++)
		dest_mino[i] = memdup(src_mino.mino_array[i], src_mino.mino_size);
	dest_mino[src_mino.mino_size] = NULL;
	return (dest_mino);
}

void	generate_mino(t_player *player)
{
	int mino_index;

	mino_index = rand() % MINO_TYPES;
	player->mino->mino_size = Tetromino[mino_index].mino_size;
	player->mino->mino_array = mino_dup(Tetromino[mino_index]);
	player->mino->current_row = 0;
	player->mino->current_col = rand() % (COLUMNS - player->mino->mino_size + 1);
}

void rotate_Tetromino(Struct *shape)
{
	Struct *temp = duplicateStruct(*shape);
	int k, size;
	size = shape->mino_size;
	for(int i = 0; i < size ; i++){
		for(int j = 0, k = size - 1; j < size; j++, k--){
				shape->mino_array[i][j] = temp->mino_array[k][i];
		}
	}
	free_array(temp);
}
