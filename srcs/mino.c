#include "tetris.h"

const t_mino Tetromino[MINO_TYPES] =
{
	{
		// S mino
		.mino_array = (char *[]) {
			(char []){0, 1, 1},
			(char []){1, 1, 0},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// Z mino
		.mino_array = (char *[]) {
			(char []){1, 1, 0},
			(char []){0, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// T mino
		.mino_array = (char *[]) {
			(char []){0, 1, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// J mino
		.mino_array = (char *[]) {
			(char []){1, 0, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// L mino
		.mino_array = (char *[]) {
			(char []){0, 0, 1},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// O mino
		.mino_array = (char *[]) {
			(char []){1, 1},
			(char []){1, 1}
		},
		.mino_size = 2
	},
	{
		// I mino
		.mino_array = (char *[]) {
			(char []){0, 0, 0, 0},
			(char []){1, 1, 1, 1},
			(char []){0, 0, 0, 0},
			(char []){0, 0, 0, 0}
		},
		.mino_size = 4
	}
};

char	*memdup(const char *src, int size)
{
	char	*dest;

	dest = (char *)xcalloc(sizeof(char), size + 1);
	memcpy(dest, src, size);
	return (dest);
}

char **mino_dup(t_mino src_mino)
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

	if (player->mino->mino_array != NULL)
		free_array(player->mino);
	mino_index = rand() % MINO_TYPES;
	player->mino->mino_size = Tetromino[mino_index].mino_size;
	player->mino->mino_array = mino_dup(Tetromino[mino_index]);
	player->mino->current_row = 0;
	player->mino->current_col = rand() % (COLUMNS - player->mino->mino_size + 1);
}

void rotate_Tetromino(t_mino *shape)
{
	t_mino *temp = duplicatet_mino(*shape);
	int k, size;
	size = shape->mino_size;
	for(int i = 0; i < size ; i++){
		for(int j = 0, k = size - 1; j < size; j++, k--){
				shape->mino_array[i][j] = temp->mino_array[k][i];
		}
	}
	free_array(temp);
}
