#include "game.h"

static bool	will_mino_collide_wall(const t_mino *mino_checker, const int height, const int width)
{
	bool	collide_left_wall;
	bool	collide_right_wall;
	bool	collide_floor;

	collide_left_wall = mino_checker->current_col + width < 0;
	collide_right_wall = mino_checker->current_col + width >= COLUMNS;
	collide_floor = mino_checker->current_row + height >= ROWS;
	return (collide_left_wall || collide_right_wall || collide_floor);
}

static bool	will_mino_collide_other_mino(const t_mino *mino_checker,
		char **table_array, const int height, const int width)
{
	int	row_where_mino_will_mode;
	int	col_where_mino_will_mode;

	row_where_mino_will_mode = mino_checker->current_row + height;
	col_where_mino_will_mode = mino_checker->current_col + width;
	return (table_array[row_where_mino_will_mode][col_where_mino_will_mode]);
}

bool	is_game_on(const t_mino *mino_checker, char **table_array)
{
	for (int h_i = 0; h_i < mino_checker->mino_size; h_i++)
	{
		for (int w_i = 0; w_i < mino_checker->mino_size; w_i++)
		{
			if (mino_checker->mino_array[h_i][w_i])
			{
				if (will_mino_collide_wall(mino_checker, h_i, w_i))
					return (false);
				if (will_mino_collide_other_mino(mino_checker, table_array, h_i, w_i))
					return (false);
			}
		}
	}
	return (true);
}
