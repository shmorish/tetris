# include "tetris.h"

void	print_map(char **map, int current_score)
{
	int i = 0;
	char str[] = "42 Tetris";
	char Buffer[ROWS][COLUMNS] = {0};

	clear();
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("Score: %d\n", current_score);
}

int do_tetris(t_tetris *tetris)
{
	int final_score;

	final_score = 0;
	while (1)
	{
		// final_scoreをprint_mapに渡すのはおかしい気がする
		print_map(tetris->map, final_score);
		move_tetris(tetris);
		if (is_gameover(tetris))
			break ;
	}
	return (final_score);
}