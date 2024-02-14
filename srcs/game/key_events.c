#include "game.h"

static int	watch_key_events(void)
{
	return (getch());
}

static void	handle_key_events(const int key_input, t_player *player)
{
	if (key_input != ERR)
	{
		if (key_input == W_KEY)
			rotate_mino(player);
		else if (key_input == S_KEY)
			move_mino_down(player);
		else if (key_input == A_KEY)
			move_mino_left(player);
		else if (key_input == D_KEY)
			move_mino_right(player);
	}
}

void	key_events(t_player *player)
{
	const int	key_input = watch_key_events();
	handle_key_events(key_input, player);
}
