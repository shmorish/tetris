#include "tetris.h"

static bool	does_mino_exist(char **mino_array, int height_index,
		int width_index)
{
	return (mino_array[height_index][width_index]);
}

static bool	will_mino_collide_wall(t_tetris *tetris, int height_index,
		int width_index)
{
	bool	collide_left_wall;
	bool	collide_right_wall;
	bool	collide_floor;

	collide_left_wall = tetris->current_col + width_index < 0;
	collide_right_wall = tetris->current_col + width_index >= COLUMNS;
	collide_floor = tetris->current_row + height_index >= ROWS;
	return (collide_left_wall || collide_right_wall || collide_floor);
}

static bool	will_mino_collide_other_mino(t_tetris *tetris, int height_index,
		int width_index)
{
	int	row_where_mino_will_mode;
	int	col_where_mino_will_mode;

	if (will_mino_collide_wall(tetris, height_index, width_index))
		return (false);
	row_where_mino_will_mode = tetris->current_row + height_index;
	col_where_mino_will_mode = tetris->current_col + width_index;
	return (tetris->table[row_where_mino_will_mode][col_where_mino_will_mode]);
}

static bool	check_mino_collision(t_tetris *tetris, char **mino_array,
		int height_index, int width_index)
{
	if (will_mino_collide_wall(tetris, height_index, width_index) == true)
	{
		if (does_mino_exist(mino_array, height_index, width_index) == true)
			return (true);
	}
	else if (will_mino_collide_other_mino(tetris, height_index, width_index) == true)
	{
		if (does_mino_exist(mino_array, height_index, width_index) == true)
			return (true);
	}
	return (false);
}

bool	can_mino_move(t_tetris *tetris, char **mino_array)
{
	int	height_index;
	int	width_index;

	height_index = 0;
	while (height_index < tetris->mino_size)
	{
		width_index = 0;
		while (width_index < tetris->mino_size)
		{
			if (check_mino_collision(tetris, mino_array, height_index, width_index))
				return (false);
			width_index++;
		}
		height_index++;
	}
	return (true);
}
