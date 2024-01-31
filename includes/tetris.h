#ifndef TETRIS_H
# define TETRIS_H

# include <libc.h>
#include <ncurses.h>

# define ROWS 20
# define COLUMNS 15

# define KEY_UP 'w'
# define KEY_LEFT 'a'
# define KEY_DOWN 's'
# define KEY_RIGHT 'd'

#define GAME_TITLE "42 Tetris"

typedef struct s_tetris
{
	char **map;
	char **tmp_map;
	int row;
	int col;
}	t_tetris;

// struct.c
t_tetris *init_struct(void);
void	destroy_struct(t_tetris *tetris);
void	map_dup(t_tetris *tetris);

// init_game.c
void	init_game(void);
void	end_game(t_tetris *tetris, int final_score);

// do_tetris.c
int do_tetris(t_tetris *tetris);

#endif