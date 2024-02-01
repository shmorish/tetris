#include "tetris.h"

int main(void)
{
	t_tetris	*tetris;

	tetris = init_struct();
	init_game();
	do_tetris(tetris);
	end_game(tetris);
	destroy_struct(tetris);
	return 0;
}

#ifdef DEBUG

__attribute__((destructor)) void end(void)
{
	int error_fd = open("error.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(error_fd, STDOUT_FILENO);
	system("leaks -q tetris");
	close(error_fd);
}

#endif
