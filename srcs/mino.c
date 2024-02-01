# include "tetris.h"

typedef struct s_struct
{
    char **array;
    int width;
}   t_mino;

static const t_mino Tetromino[7] = {
    {
		// S mino
		// green
        .array = (char *[]) {
            (char []){0, 1, 1},
            (char []){1, 1, 0},
            (char []){0, 0, 0}
        },
        .width = 3
    },
	{
		// Z mino
		// red
		.array = (char *[]) {
			(char []){1, 1, 0},
			(char []){0, 1, 1},
			(char []){0, 0, 0}
		},
		.width = 3
	},
	{
		// T mino
		// purple
		.array = (char *[]) {
			(char []){0, 1, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.width = 3
	},
	{
		// J mino
		// blue
		.array = (char *[]) {
			(char []){1, 0, 0},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.width = 3
	},
	{
		// L mino
		// orange
		.array = (char *[]) {
			(char []){0, 0, 1},
			(char []){1, 1, 1},
			(char []){0, 0, 0}
		},
		.width = 3
	},
	{
		// O mino
		// yellow
		.array = (char *[]) {
			(char []){1, 1},
			(char []){1, 1}
		},
		.width = 2
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
		.width = 4
	}
};

char   **mino_alloc(char **mino, int size)
{
    char **array;
    int i;

	array = (char **)xcalloc(sizeof(char *), size + 1);
    i = 0;
    while (i < size)
    {
		array[i] = memdup(mino[i], size);
        if (!array[i])
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        i++;
    }

	array[i] = NULL;
    return (array);
}

void    generate_mino(t_tetris *tetris)
{
	int index = rand() % 7;
    tetris->mino_size = Tetromino[index].width;
	tetris->mino_data = mino_alloc(Tetromino[index].array, tetris->mino_size);
	tetris->current_row = 0;
    tetris->current_col = rand() % (COLUMNS - tetris->mino_size + 1);
}
