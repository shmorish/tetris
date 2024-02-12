#include "mino.h"

static const t_mino Tetromino[MINO_TYPES] =
{
	{
		// S mino
		.mino_array = (char *[])
		{
			(char []){0, 1, 1},
			(char []){1, 1, 0},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// Z mino
		.mino_array = (char *[])
		{
			(char []){1, 1, 0},
			(char []){0, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// T mino
		.mino_array = (char *[])
		{
			(char []){0, 1, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// J mino
		.mino_array = (char *[])
		{
			(char []){1, 0, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// L mino
		.mino_array = (char *[])
		{
			(char []){0, 0, 1},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.mino_size = 3
	},
	{
		// O mino
		.mino_array = (char *[])
		{
			(char []){1, 1},
			(char []){1, 1}
		},
		.mino_size = 2
	},
	{
		// I mino
		.mino_array = (char *[])
		{
			(char []){0, 0, 0, 0},
			(char []){1, 1, 1, 1},
			(char []){0, 0, 0, 0},
			(char []){0, 0, 0, 0}
		},
		.mino_size = 4
	}
};

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
