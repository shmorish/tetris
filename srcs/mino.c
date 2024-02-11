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

void	destruct_player_struct(t_player *player)
{
	destruct_table_struct(player->table);
	destruct_mino_struct(player->mino);
	free(player);
	player = NULL;
}

void	destruct_table_struct(t_table *table)
{
	free_array(table->table_array);
	free(table);
	table = NULL;
}

void	destruct_mino_struct(t_mino *mino)
{
	free_array(mino->mino_array);
	free(mino);
	mino = NULL;
}

char	*memdup(const char *src, int size)
{
	char	*dest;

	dest = (char *)xmalloc(sizeof(char) * (size + 1));
	memcpy(dest, src, size);
	return (dest);
}

static char	**mino_dup(char **mino, int size)
{
	char	**array;

	array = (char **)xmalloc(sizeof(char *) * (size + 1));
	for (int i = 0; i < size; i++)
		array[i] = memdup(mino[i], size);
	array[size] = NULL;
	return (array);
}

void	generate_mino(t_mino *mino)
{
	int mino_index;

	mino_index = rand() % MINO_TYPES;
	mino->mino_size = Tetromino[mino_index].mino_size;
	mino->mino_array = mino_dup(Tetromino[mino_index].mino_array, mino->mino_size);
	mino->current_row = 0;
	mino->current_col = rand() % (COLUMNS - mino->mino_size + 1);
}

void	generate_new_mino(t_mino *mino)
{
	free_array(mino->mino_array);
	mino->mino_array = NULL;
	generate_mino(mino);
}

void rotate_Tetromino(t_mino *mino)
{
	t_mino *tmp = duplicate_mino(mino);
	int k, size;
	size = mino->mino_size;
	for(int i = 0; i < size ; i++){
		for(int j = 0, k = size - 1; j < size; j++, k--)
				mino->mino_array[i][j] = tmp->mino_array[k][i];
	}
	destruct_mino_struct(tmp);
}
