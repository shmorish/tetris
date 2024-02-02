#ifndef TETRIS_H
# define TETRIS_H

# include "define.h"

// actions.c
void		rotate_mino(t_tetris *tetris, t_tetris *tmp);
void		move_mino(t_tetris *tetris, t_tetris *tmp, int direction);
void		move_down(t_tetris *tetris, t_tetris *tmp);

// clear_mino.c
int			clear_mino(t_tetris *tetris);

// can_mino_move.c
bool		can_mino_move(t_tetris *tetris, char **mino_array);

// do_tetris.c
void		do_tetris(t_tetris *tetris);

// game_utils.c
void		init_game(void);
void		end_game(t_tetris *tetris);

// mino.c
void		generate_mino(t_tetris *tetris);
char		**mino_alloc(char **mino, int size);

// print_table.c
void		print_table(int situation, t_tetris *tetris, int score);

// struct.c
t_tetris	*init_struct(void);
void		destroy_struct(t_tetris *tetris);
t_tetris	*dup_mino_data(t_tetris *tetris);

// utils.c
void		*xcalloc(size_t count, size_t size);
char		*memdup(const char *src, int size);
void		free_array(char **str);
char		**table_alloc(char **table);

// time.c
void		update_exec_time(void);
bool		has_time_elapsed(t_tetris *tetris);

#endif
