#ifndef TETRIS_H
# define TETRIS_H

# include "define.h"

// actions.c
void		rotate_mino(t_tetris *tetris);
void		move_mino_left(t_tetris *tetris);
void		move_mino_right(t_tetris *tetris);
void		move_mino_down(t_tetris *tetris);

// clear_mino.c
int			clear_mino(t_tetris *tetris);

// can_mino_move.c
bool		can_mino_move(const t_tetris *tetris);

// do_tetris.c
void		do_tetris(t_tetris *tetris);

// game_utils.c
void		init_game(void);
void		end_game(t_tetris *tetris);

// mino.c
void		generate_mino(t_tetris *tetris);
char		**mino_alloc(char **mino, int size);

// print_table.c
void		print_table(bool situation, const t_tetris *tetris, int score);

// struct.c
t_tetris	*init_struct(void);
void		destroy_struct(t_tetris *tetris);
t_tetris	*dup_tetris_struct(t_tetris *tetris);

// utils.c
void		*xcalloc(size_t count, size_t size);
char		*memdup(const char *src, int size);
void		free_array(char **str);
char		**table_dup(char **table);
char		**init_table(void);

// time.c
void		init_time(void);
void		print_output_according_to_fps(const t_tetris *tetris);
void		update_exec_time(void);
bool		time_elapsed(t_tetris *tetris);

#endif
