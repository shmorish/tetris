#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
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
    char **array;
    int width, row, col;
} Struct;

#endif