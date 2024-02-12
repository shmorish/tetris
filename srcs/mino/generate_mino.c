#include "mino.h"

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
