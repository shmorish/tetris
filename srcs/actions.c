#include "tetris.h"

static int decrease_time = 1000;

void	rotate_mino(t_tetris *tetris)
{
	rotate_tmp_mino(tetris);
	if (possible_to_move(tetris))
		rotate_mino_data(tetris);
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