#include "tetris_before.h"

const Struct Tetromino[7] = {
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

Struct *generateTetromino()
{
	// Struct shape = Tetromino[rand() % 7];
	Struct shape = Tetromino[6];
	shape.col = rand() % (COLUMNS - shape.width + 1);
	shape.row = 0;
	return duplicateStruct(shape);
}

void rotate_Tetromino(Struct *shape)
{
	Struct *temp = duplicateStruct(*shape);
	int k, width;
	width = shape->width;
	for(int i = 0; i < width ; i++){
		for(int j = 0, k = width - 1; j < width; j++, k--){
				shape->array[i][j] = temp->array[k][i];
		}
	}
	free_array(temp);
}
