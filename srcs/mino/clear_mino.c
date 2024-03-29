#include "mino.h"
#define INITIAL_TIME_TO_DECREASE 10000
#define ADDEND_TIME_TO_DECREASE 1000

static int	time_to_decrease = INITIAL_TIME_TO_DECREASE;

static bool	is_row_complete(const t_player *player, int row)
{
	for (int col_i = 0; col_i < COLUMNS; col_i++)
	{
		if (player->table->table_array[row][col_i] == 0)
			return (false);
	}
	return (true);
}

static void	remove_row(t_player *player, int row)
{
	for (int col_i = 0; col_i < COLUMNS; col_i++)
		player->table->table_array[row][col_i] = 0;
}

static void	shift_rows_down(t_player *player, int empty_row)
{
	for (int row_i = empty_row; row_i > 0; row_i--)
		for (int col_i = 0; col_i < COLUMNS; col_i++)
			player->table->table_array[row_i][col_i] = player->table->table_array[row_i - 1][col_i];
}

int	clear_mino(t_player *player)
{
	int	clear_row_count;

	clear_row_count = 0;
	for (int row_i = 0; row_i < ROWS; row_i++)
	{
		if (is_row_complete(player, row_i))
		{
			clear_row_count++;
			remove_row(player, row_i);
			shift_rows_down(player, row_i);
			if (time_to_decrease > 0)
			{
				player->table->time_to_execute -= time_to_decrease;
				time_to_decrease += ADDEND_TIME_TO_DECREASE;
			}
			// 再検証を行うためにインデックスをデクリメント
			row_i--;
		}
	}
	return (clear_row_count * SCORE_PER_BLOCK * COLUMNS);
}
