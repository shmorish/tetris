# include "tetris.h"

typedef enum e_color{
	GREEN,
	RED,
	PURPLE,
	BLUE,
	ORANGE,
	YELLOW,
	CYAN
} e_color;

typedef struct {
    char	**array;
    int		width;
    e_color	color;
} Tetromino;

char	**createArray(int rows, int cols, char blocks[rows][cols])
{
    char **array = xcalloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        array[i] = xcalloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) {
            array[i][j] = blocks[i][j];
        }
    }
    return array;
}

void freeArray(char** array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

Tetromino createTetromino(char blocks[][4], int width, e_color color)
{
    int rows = sizeof(blocks) / sizeof(blocks[0]);
    int cols = sizeof(blocks[0]) / sizeof(char);
    return (Tetromino){.array = createArray(rows, cols, blocks), .width = width, .color = color};
}

// int main() {
//     Tetromino tetrominos[7] = {
//         createTetromino((char[][4]){{0, 1, 1, 0}, {1, 1, 0, 0}}, 3, COLOR_GREEN),
//         createTetromino((char[][4]){{1, 1, 0, 0}, {0, 1, 1, 0}}, 3, COLOR_RED),
//         // ... 他のテトリミノも同様に初期化 ...
//     };

//     // 使用後、確保したメモリを解放
//     for (int i = 0; i < 7; i++) {
//         freeArray(tetrominos[i].array, tetrominos[i].width);
//     }

//     return 0;
// }
