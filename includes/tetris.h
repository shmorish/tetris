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
# define SCORE_PER_BLOCK 100
# define INITIAL_TIME_TO_EXECVE_ms 400000
# define MAP_EMPTY '.'
# define MAP_FULL '#'

# define GAME_ON true
# define GAME_OVER false

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
t_mino			*duplicate_mino(t_mino shape);
void			free_array(char **str);
void			destruct_mino_struct(t_mino *mino);
void			destruct_table_struct(t_table *table);
void			destruct_player_struct(t_player *player);

// game_setup.c
void			init_game(void);
void			end_game(t_player *player);

// mino.c
void			generate_mino(t_player *player);
void			generate_new_mino(t_player *player);
void			rotate_Tetromino(t_mino *shape);

// run_tetris_game.c
void			key_events(t_player *player);
int				isGameActive(t_mino *movable_check_mino, t_player *player);

// time.c
void			init_time(void);
void			update_exec_time(void);
bool			time_elapsed(t_table *table);

#endif
