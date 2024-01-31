#include "tetris.h"

int	switch_print(int key_input, const char * restrict format, ...);
{
	if (key_input == 'w')
		return (printw(format));
	else if (key_input == 'f')
		return (printf(format));
	strerror("invalid key_input");
	return (ERR);
}