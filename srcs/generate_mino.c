#include "tetris.h"

typedef struct s_struct
{
	char	**array;
	int		size;
}			t_mino;

static const t_mino Tetromino[MINO_TYPES] =
{
	{
		// S mino
		// green
		.array = (char *[]) {
			(char []){0, 1, 1},
			(char []){1, 1, 0},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// Z mino
		// red
		.array = (char *[]) {
			(char []){1, 1, 0},
			(char []){0, 1, 1},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// T mino
		// purple
		.array = (char *[]) {
			(char []){0, 1, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// J mino
		// blue
		.array = (char *[]) {
			(char []){1, 0, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// L mino
		// orange
		.array = (char *[]) {
			(char []){0, 0, 1},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.size = 3
	},
	{
		// O mino
		// yellow
		.array = (char *[]) {
			(char []){1, 1},
			(char []){1, 1}
		},
		.size = 2
	},
	{
		// I mino
		// cyan
		.array = (char *[]) {
			(char []){0, 0, 0, 0},
			(char []){1, 1, 1, 1},
			(char []){0, 0, 0, 0},
			(char []){0, 0, 0, 0}
		},
		.size = 4
	}
};

void	generate_mino(t_tetris *tetris)
{
	int	mino_index;

	mino_index = rand() % MINO_TYPES;
	tetris->mino_size = Tetromino[mino_index].size;
	tetris->mino_data = mino_dup(Tetromino[mino_index].array, tetris->mino_size);
	tetris->current_row = 0;
	tetris->current_col = rand() % (COLUMNS - tetris->mino_size + 1);
}
