#include "tetris.h"

static char	**init_table(void);

t_tetris	*init_struct(void)
{
	t_tetris	*tetris;

	tetris = (t_tetris *)xcalloc(sizeof(t_tetris), 1);
	tetris->mino_data = NULL;
	tetris->mino_size = 0;
	tetris->current_row = 0;
	tetris->current_col = 0;
	tetris->time_to_execute = 400000;
	tetris->table = init_table();
	tetris->score = 0;
	tetris->game_on = true;
	return (tetris);
}

void	destroy_struct(t_tetris *tetris)
{
	free_array(tetris->mino_data);
	free_array(tetris->table);
	free(tetris);
	tetris = NULL;
}

t_tetris	*dup_mino_data(t_tetris *tetris)
{
	t_tetris	*tmp;

	tmp = init_struct();
	tmp->mino_data = mino_alloc(tetris->mino_data, tetris->mino_size);
	tmp->mino_size = tetris->mino_size;
	tmp->current_row = tetris->current_row;
	tmp->current_col = tetris->current_col;
	tmp->time_to_execute = tetris->time_to_execute;
	free_array(tmp->table);
	tmp->table = mino_alloc(tetris->table, ROWS);
	tmp->score = tetris->score;
	tmp->game_on = tetris->game_on;
	return (tmp);
}

static char	**init_table(void)
{
	int		i;
	char	**table;

	table = (char **)xcalloc(sizeof(char *), ROWS + 1);
	i = 0;
	while (i < ROWS)
	{
		table[i] = (char *)xcalloc(sizeof(char), COLUMNS + 1);
		i++;
	}
	table[i] = NULL;
	return (table);
}
