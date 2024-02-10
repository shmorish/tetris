#include "tetris.h"
#define W_KEY 'w'
#define A_KEY 'a'
#define S_KEY 's'
#define D_KEY 'd'

static int time_to_decrease = 1000;

void	rotate_mino(t_player *player)
{
	t_mino	*movable_check_mino;

	movable_check_mino = duplicate_mino(*player->mino);
	rotate_Tetromino(movable_check_mino);
	if (isGameActive(movable_check_mino, player))
		rotate_Tetromino(player->mino);
	destruct_mino_struct(movable_check_mino);
}

static void	put_mino_data_to_table(t_player *player)
{
	for (int y = 0; y < player->mino->mino_size; y++)
		for (int x = 0; x < player->mino->mino_size; x++)
			if (player->mino->mino_array[y][x] != 0)
				player->table->table_array[player->mino->current_row + y][player->mino->current_col + x] = player->mino->mino_array[y][x];
}

static bool is_row_complete(const t_player *player, int row)
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
	{
		player->table->table_array[row][col_i] = 0;
	}
}

static void shift_rows_down(t_player *player, int empty_row)
{
	for (int row = empty_row; row > 0; row--)
		for (int col = 0; col < COLUMNS; col++)
			player->table->table_array[row][col] = player->table->table_array[row - 1][col];
}

static int	clear_mino(t_player *player)
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
				time_to_decrease--;
			}
			// 再検証を行うためにインデックスをデクリメント
			row_i--;
		}
	}
	return (clear_row_count * SCORE_PER_BLOCK * COLUMNS);
}

void	move_mino_down(t_player *player)
{
	t_mino	*movable_check_mino;

	movable_check_mino = duplicate_mino(*player->mino);
	movable_check_mino->current_row++;
	if (isGameActive(movable_check_mino, player))
		player->mino->current_row++;
	else
	{
		put_mino_data_to_table(player);
		player->table->score += clear_mino(player);
		generate_new_mino(player);
		if (isGameActive(movable_check_mino, player))
			player->table->is_game_on = GAME_OVER;
	}
	destruct_mino_struct(movable_check_mino);
}

void	key_events(t_player *player)
{
	int	key_input;

	key_input = getch();
	if (key_input != ERR)
	{
		if (key_input == W_KEY)
			rotate_mino(player);
		else if (key_input == S_KEY)
			move_mino_down(player);
		else if (key_input == A_KEY)
			move_mino_left(player);
		else if (key_input == D_KEY)
			move_mino_right(player);
	}
}
