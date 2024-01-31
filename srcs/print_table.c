#include "tetris.h"

int	switch_print(int situation, const char * restrict format, ...)
{
	if (situation == GAME_ON)
		return (printw(format));
	else if (situation == GAME_OVER)
		return (printf(format));
	strerror("invalid situation");
	return (ERR);
}

void	print_title(void)
{
	int title_len = strlen(GAME_TITLE);

	clear();
	for (int i = 0; i < COLUMNS - title_len - 1; i++)
		printw(" ");
	switch_print(GAME_ON, "%s\n", GAME_TITLE);
}

void	print_table(int situation, char **table, int score)
{
	if (situation == GAME_ON)
		print_title();
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			printf("%c ", table[i][j]);
		}
		printf("\n");
	}
	if (situation == GAME_OVER)
		switch_print(situation, "\nGame over!\n");
	switch_print(situation, "\nScore: %d\n", score);
}