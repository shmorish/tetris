#include "utils.h"

void	store_mino_to_table(t_mino *mino, char **table)
{
	for (int h_i = 0; h_i < mino->mino_size; h_i++)
		for (int w_i = 0; w_i < mino->mino_size; w_i++)
			if (mino->mino_array[h_i][w_i] != 0)
				table[mino->current_row + h_i][mino->current_col + w_i] = mino->mino_array[h_i][w_i];
}
