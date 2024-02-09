#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <stdbool.h>

#define ROWS 20
#define COLUMNS 15
#define INITIAL_TIME_TO_EXECVE_ms 400000

struct timeval before_now, now;

typedef struct Struct
{
    char	**mino_array;
    int		mino_size;
	int		current_row;
	int		current_col;
} Struct;

typedef struct s_mino
{
	// mino data
	char				**mino_array;
	int					mino_size;
	int					current_row;
	int					current_col;
}	t_mino;

typedef struct s_table
{
	// table data
	suseconds_t		time_to_execute;
	char			**table_array;
	long			score;
	bool			is_game_on;
}	t_table;

/* ファイルに存在する変数をすべてこの構造体に格納する */
typedef struct s_player
{
	t_mino		*mino;
	t_table		*table;
}				t_player;

void print_game(Struct *current, t_player *player);
void print_game_over(t_player *player);

// alloc.c
void *xmalloc(size_t size);
Struct *duplicateStruct(Struct shape);
void free_array(Struct *shape);

// mino.c
Struct *generateTetromino();
void	generate_mino(t_player *player);

void rotate_Tetromino(Struct *shape);
#endif
