#ifndef TETRIS_H
# define TETRIS_H

# include <libc.h>
#include <ncurses.h>

# define ROWS 20
# define COLUMNS 15

typedef struct s_tetris
{
	char **map;
	int row;
	int col;
}	t_tetris;

#endif