#include "tetris.h"

static int decrease_time = 1000;

static bool	possible_to_move(t_tetris *tetris, int row, int col)
{
	char **array = tetris->tmp_mino_data;

	for (int i = 0; i < tetris->mino_size; i++){
		for (int j = 0; j < tetris->mino_size; j++){
			if((col + j < 0 || col + j >= COLUMNS || row + i >= ROWS)){
				if(array[i][j])
					return false;
			}
			else if(tetris->table[row + i][col + j] && array[i][j])
				return false;
		}
	}
	return true;
}

void rotate(t_tetris *tetris, int dimension)
{
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            int oppositeIndex = dimension - 1 - j;
            tetris->tmp_mino_data[i][j] = tetris->mino_data[oppositeIndex][i];
        }
    }
}


void	rotate_mino(t_tetris *tetris)
{
	rotate(tetris->tmp_mino_data, tetris->mino_size);
	if (possible_to_move(tetris, tetris->current_row, tetris->current_col))
		rotate(tetris->mino_data, tetris->mino_size);
}

void	move_mino(t_tetris *tetris, int direction)
{
	if (possible_to_move(tetris, tetris->current_row, tetris->current_col + direction))
	{
		tetris->current_col += direction;
	}
}

void	move_down(t_tetris *tetris)
{
	if (possible_to_move(tetris, tetris->current_row + 1, tetris->current_col))
	{
		tetris->current_row++;
	}
	else if (decrease_time > 0)
	{
		tetris->time_to_execute -= decrease_time;
		decrease_time--;
	}
}