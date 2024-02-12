#include "utils.h"

void	store_mino_to_table(t_mino *mino, char **table)
{
	for (int y = 0; y < mino->mino_size; y++)
		for (int x = 0; x < mino->mino_size; x++)
			if (mino->mino_array[y][x] != 0)
				table[mino->current_row + y][mino->current_col + x] = mino->mino_array[y][x];
}
