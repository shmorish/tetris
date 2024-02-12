#ifndef GAME_H
# define GAME_H

# include "utils.h"
// game_setup.c
void	init_game(void);
void	end_game(t_player *player);

// is_game_on.c
bool	is_game_on(const t_mino *mino_checker, char **table_array);

// run_tetris_game.c
void	put_mino_data_to_table(t_mino *mino, char **table);
void	run_tetris_game(t_player *player);

#endif
