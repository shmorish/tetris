#ifndef TETRIS_H
# define TETRIS_H

# include <ncurses.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>

# define ROWS 20
# define COLUMNS 15
# define MINO_TYPES 7
# define INITIAL_TIME_TO_EXECVE_ms 400000
# define MAP_EMPTY '.'
# define MAP_FULL '#'

struct timeval before_now, now;

typedef struct s_mino
{
	// mino data
	char		**mino_array;
	int			mino_size;
	int			current_row;
	int			current_col;
}				t_mino;

typedef struct s_table
{
	// table data
	suseconds_t	time_to_execute;
	char		**table_array;
	long		score;
	bool		is_game_on;
}				t_table;

/* ファイルに存在する変数をすべてこの構造体に格納する */
typedef struct s_player
{
	t_mino		*mino;
	t_table		*table;
}				t_player;

void			print_game(t_mino *current, t_player *player);
void			print_game_over(t_player *player);

// alloc.c
void			*xmalloc(size_t size);
t_mino			*duplicatet_mino(t_mino shape);
void			free_array(char **str);
void			destruct_mino_struct(t_mino *mino);

// mino.c
void			generate_mino(t_player *player);
void			generate_new_mino(t_player *player);
void			rotate_Tetromino(t_mino *shape);

#endif
