#include "tetris.h"

static bool	will_mino_collide_wall(const t_tetris *tetris, int height,
		int width)
{
	bool	collide_left_wall;
	bool	collide_right_wall;
	bool	collide_floor;

	collide_left_wall = tetris->current_col + width < 0;
	collide_right_wall = tetris->current_col + width >= COLUMNS;
	collide_floor = tetris->current_row + height >= ROWS;
	return (collide_left_wall || collide_right_wall || collide_floor);
}

static bool	will_mino_collide_other_mino(const t_tetris *tetris, int height,
		int width)
{
	int	row_where_mino_will_mode;
	int	col_where_mino_will_mode;

	row_where_mino_will_mode = tetris->current_row + height;
	col_where_mino_will_mode = tetris->current_col + width;
	return (tetris->table[row_where_mino_will_mode][col_where_mino_will_mode]);
}

bool	can_mino_move(const t_tetris *tetris)
{
	for (int height = 0; height < tetris->mino_size; height++)
	{
		for (int width = 0; width < tetris->mino_size; width++)
		{
			if (tetris->mino_data[height][width])
			{
				if (will_mino_collide_wall(tetris, height, width))
					return (false);
				if (will_mino_collide_other_mino(tetris, height, width))
					return (false);
			}
		}
	}
	return (true);
}
