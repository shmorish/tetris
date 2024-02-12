#ifndef PRINT_H
# define PRINT_H

# include "utils.h"
# define MAP_EMPTY '.'
# define MAP_FULL '#'
# define GAME_TITLE "42 Tetris"

// print_table.c
void	print_table(const bool situation, const t_player *player, int score);

#endif
