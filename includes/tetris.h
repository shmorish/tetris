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

#define GAME_OVER 0
#define GAME_ON 1

#define MAP_EMPTY '.'
#define MAP_FULL '#'

typedef struct s_tetris
{
	// mino data
	char **mino_data;
	char **tmp_mino_data;
	int mino_size;
	int current_row;
	int current_col;

	// game data
	suseconds_t time_to_execute;
	char **table;
	char **tmp_table;
	int score;
}	t_tetris;

// struct.c
t_tetris *init_struct(void);
void	destroy_struct(t_tetris *tetris);
void	map_dup(t_tetris *tetris);
void	*xcalloc(size_t size);
void	free_array(char **str);

// init_game.c
void	init_game(void);
void	end_game(t_tetris *tetris);

// do_tetris.c
void	do_tetris(t_tetris *tetris);

// print_game.c
int	switch_print(int key_input, const char * restrict format, ...);

#endif