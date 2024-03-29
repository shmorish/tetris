#ifndef DEFINE_H
# define DEFINE_H

# include <ncurses.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

# define ROWS 20
# define COLUMNS 15

# define W_KEY 'w'
# define A_KEY 'a'
# define S_KEY 's'
# define D_KEY 'd'

# define GAME_TITLE "42 Tetris"

# define SCORE_PER_BLOCK 100

# define FIRST_EXEC_TIME 400000
# define MINO_TYPES 7

# define GAME_OVER false
# define GAME_ON true

# define MAP_EMPTY '.'
# define MAP_FULL '#'

# define FPS 60

typedef struct s_tetris
{
	// mino data
	char			**mino_data;
	int				mino_size;
	int				current_row;
	int				current_col;

	// game data
	suseconds_t		time_to_execute;
	char			**table;
	long			score;
	bool			game_on;
}				t_tetris;

#endif
