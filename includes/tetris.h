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

// alloc.c
void			*xmalloc(size_t size);
t_mino			*duplicate_mino(t_mino *shape);
void			free_array(char **str);
void			destruct_mino_struct(t_mino *mino);
void			destruct_table_struct(t_table *table);
void			destruct_player_struct(t_player *player);

// game_setup.c
void			init_game(void);
void			end_game(t_player *player);

// mino.c
void			generate_mino(t_mino *mino);
void			generate_new_mino(t_mino *mino);
void			rotate_Tetromino(t_mino *shape);

// print_table.c
void			print_table(const bool situation, const t_player *player, int score);

// run_tetris_game.c
void			key_events(t_player *player);
int				can_mino_move(t_mino *check_mino, char **table);
void			time_elapse_event(t_player *player);
void			put_mino_data_to_table(t_mino *mino, char **table);

// time.c
void			init_time(void);
void			update_exec_time(void);
bool			time_elapsed(t_table *table);
void			print_output_according_to_fps(const t_player *player);

// struct.c
char	**init_table(void);
t_player	*init_struct(void);

#endif
