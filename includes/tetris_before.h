#ifndef TETRIS_BEFORE_H
#define TETRIS_BEFORE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <stdbool.h>

#define ROWS 20
#define COLUMNS 15

struct timeval before_now, now;

typedef struct Struct
{
    char	**array;
    int		width;
	int		row;
	int		col;
} Struct;

void print_game(int score, Struct *current, char Table[ROWS][COLUMNS]);
void print_game_over(int final_score, char Table[ROWS][COLUMNS]);

// alloc.c
void *xmalloc(size_t size);
Struct *duplicateStruct(Struct shape);
void free_array(Struct *shape);

// mino.c
Struct *generateTetromino();
void rotate_Tetromino(Struct *shape);
#endif