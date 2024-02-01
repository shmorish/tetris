#ifndef TETRIS_H
# define TETRIS_H

# include <libc.h>
#include <ncurses.h>

# define ROWS 20
# define COLUMNS 15

# define W_KEY 'w'
# define A_KEY 'a'
# define S_KEY 's'
# define D_KEY 'd'

#define GAME_TITLE "42 Tetris"

#define GAME_OVER 0
#define GAME_ON 1

#define MAP_EMPTY '.'
#define MAP_FULL '#'

typedef struct s_tetris
{
	// mino data
	char **mino_data;
	int mino_size;
	int current_row;
	int current_col;

	// game data
	suseconds_t time_to_execute;
	char **table;
	int score;
	bool game_on;
}	t_tetris;

// actions.c
bool		possible_to_move(t_tetris *tetris, char **array);
void		rotate_mino(t_tetris *tetris, t_tetris *tmp);
void		move_mino(t_tetris *tetris, t_tetris *tmp, int direction);
void		move_down(t_tetris *tetris, t_tetris *tmp);

// do_tetris.c
void 		do_tetris(t_tetris *tetris);

// game_utils.c
void		init_game(void);
void		end_game(t_tetris *tetris);

// mino.c
void		generate_mino(t_tetris *tetris);
char		**mino_alloc(char **mino, int size);

// print_table.c
void		print_table(int situation, t_tetris *tetris, int score);

// struct.c
t_tetris 	*init_struct(void);
void		destroy_struct(t_tetris *tetris);
t_tetris	*dup_mino_data(t_tetris *tetris);

// utils.c
void		*xcalloc(size_t count, size_t size);
char		*memdup(const char *src, int size);
void		free_array(char **str);
char		**table_alloc(char **table);

// time.c
void		update_exec_time(void);
int			time_elapses(t_tetris *tetris);

#endif
