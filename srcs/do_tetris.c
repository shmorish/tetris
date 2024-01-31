# include "tetris.h"

void	print_map(char **map, int current_score)
{
	int i = 0;
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
	int final_score = 0;

	while (1)
	{
		int key_input = getch();
		if (key_input != ERR)
		{
			if (key_input == KEY_UP)
				rotate_tetris(tetris);
			else if (key_input == KEY_DOWN)
				accelerate_tetris(tetris, 1);
			else if (key_input == KEY_LEFT)
				move_tetris(tetris, -1);
			else if (key_input == KEY_RIGHT)
				move_tetris(tetris, 1);
		}
		// final_scoreをprint_mapに渡すのはおかしい気がする
		// print_map(tetris->map, final_score);
		// move_tetris(tetris);
		// if (is_gameover(tetris))
		break ;
	}
	return (final_score);
}