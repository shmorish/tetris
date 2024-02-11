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
# define FPS 60
# define MAP_EMPTY '.'
# define MAP_FULL '#'

# define GAME_TITLE "42 Tetris"

# define GAME_ON true
# define GAME_OVER false

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

const t_mino Tetromino[MINO_TYPES];

// alloc_utils.c
void		*xmalloc(size_t size);
void		free_array(char **array);
void		*memdup(const void *src, size_t size);

// clear_mino.c
int			clear_mino(t_player *player);

// game_setup.c
void		init_game(void);
void		end_game(t_player *player);

// generate_mino.c
void		generate_mino(t_mino *mino);
void		generate_new_mino(t_mino *mino);

// mino_alloc.c
t_mino		*duplicate_mino(t_mino *mino);
char		**mino_dup(char **mino_array, int mino_size);

// mino_movement.c
void		rotate_mino(t_player *player);
void		move_mino_down(t_player *player);
void		move_mino_left(t_player *player);
void		move_mino_right(t_player *player);

// print_table.c
void		print_table(const bool situation, const t_player *player, int score);

// run_tetris_game.c
void		put_mino_data_to_table(t_mino *mino, char **table);
void		run_tetris_game(t_player *player);

void			print_table(const bool situation, const t_player *player,
					int score);

// time.c
void			init_time(void);
void			update_exec_time(void);
bool			time_elapsed(t_table *table);
void			print_output_according_to_fps(const t_player *player);

// can_mino_move.c
bool			can_mino_move(const t_mino *mino_checker, char **table_array);

// struct.c
t_player	*init_struct(void);
void		destruct_player_struct(t_player *player);
void		destruct_mino_struct(t_mino *mino);
void		destruct_table_struct(t_table *table);

// table_alloc.c
char		**init_table(void);

// time.c
void		init_time(void);
bool		time_elapsed(t_table *table);
void		update_exec_time(void);
void		print_output_according_to_fps(const t_player *player);
#endif
