#ifndef MINO_H
# define MINO_H

# include "utils.h"

# define MINO_TYPES 7
# define SCORE_PER_BLOCK 100
const t_mino	Tetromino[MINO_TYPES];

// clear_mino.c
int				clear_mino(t_player *player);

// generate_mino.c
void			generate_mino(t_mino *mino);
void			generate_new_mino(t_mino *mino);

// mino_movement.c
void			rotate_mino(t_player *player);
void			move_mino_down(t_player *player);
void			move_mino_left(t_player *player);
void			move_mino_right(t_player *player);

#endif
