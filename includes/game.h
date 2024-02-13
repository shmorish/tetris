#ifndef GAME_H
# define GAME_H

# include "mino.h"
# include "utils.h"

# define W_KEY 'w'
# define A_KEY 'a'
# define S_KEY 's'
# define D_KEY 'd'

// game_setup.c
void	init_game(void);
void	end_game(t_player *player);

// is_game_on.c
bool	is_game_on(const t_mino *mino_checker, char **table_array);

// run_game.c
void	run_game(t_player *player);

// key_events.c
void	key_events(t_player *player);

#endif
