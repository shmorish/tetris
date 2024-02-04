#include "tetris.h"

t_tetris	*init_struct(void)
{
	t_tetris	*tetris;

	tetris = (t_tetris *)xcalloc(sizeof(t_tetris), 1);
	tetris->mino_data = NULL;
	tetris->mino_size = 0;
	tetris->current_row = 0;
	tetris->current_col = 0;
	tetris->time_to_execute = FIRST_EXEC_TIME;
	tetris->table = init_table();
	tetris->score = 0;
	tetris->game_on = GAME_ON;
	return tetris;
}

void	destroy_struct(t_tetris *tetris)
{
	free_array(tetris->mino_data);
	free_array(tetris->table);
	free(tetris);
	tetris = NULL;
}

t_tetris	*dup_tetris_struct(t_tetris *tetris)
{
	t_tetris	*duped_struct;

	duped_struct = init_struct();
	duped_struct->mino_data = mino_alloc(tetris->mino_data, tetris->mino_size);
	duped_struct->mino_size = tetris->mino_size;
	duped_struct->current_row = tetris->current_row;
	duped_struct->current_col = tetris->current_col;
	duped_struct->time_to_execute = tetris->time_to_execute;
	free_array(duped_struct->table);
	duped_struct->table = table_dup(tetris->table);
	duped_struct->score = tetris->score;
	duped_struct->game_on = tetris->game_on;
	return duped_struct;
}
