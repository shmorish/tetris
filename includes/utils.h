#ifndef UTILS_H
# define UTILS_H

# include <ncurses.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>

# define ROWS 20
# define COLUMNS 15
# define INITIAL_TIME_TO_EXECVE_ms 400000
# define FPS 60
# define GAME_ON true
# define GAME_OVER false
# define MAP_EMPTY '.'
# define MAP_FULL '#'
# define GAME_TITLE "42 Tetris"

typedef struct s_mino
{
	char		**mino_array;
	int			mino_size;
	int			current_row;
	int			current_col;
}				t_mino;

typedef struct s_table
{
	suseconds_t	time_to_execute;
	char		**table_array;
	long		score;
	bool		is_game_on;
}				t_table;

typedef struct s_player
{
	t_mino		*mino;
	t_table		*table;
}				t_player;

// alloc.c
t_player		*init_struct(void);
char			**init_table(void);
t_mino			*duplicate_mino(t_mino *mino);
char			**mino_dup(char **mino_array, int mino_size);

// free.h
void			free_array(char **array);
void			destruct_player_struct(t_player *player);
void			destruct_mino_struct(t_mino *mino);
void			destruct_table_struct(t_table *table);

// time.c
void			init_time(void);
bool			time_elapsed(t_table *table);
void			update_exec_time(void);
void			print_output_according_to_fps(const t_player *player);

// store.c
void			store_mino_to_table(t_mino *mino, char **table);

// print.c
void			print_table(const bool situation, const t_player *player, int score);

#endif
