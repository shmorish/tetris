#include "tetris.h"


int switch_print(int situation, const char * restrict format, ...) {
    va_list args;
    int result = 0;

    va_start(args, format);
    if (situation == GAME_ON) {
        vwprintw(stdscr, format, args);
        refresh();
    } else if (situation == GAME_OVER) {
        result = vprintf(format, args);
    } else {
        perror("invalid situation");
        result = ERR;
    }
    va_end(args);
    return result;
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
			switch_print(situation, "%c ", table[i][j] ? MAP_FULL : MAP_EMPTY);
		}
		switch_print(situation, "\n");
	}
	if (situation == GAME_OVER)
		switch_print(situation, "\nGame over!\n");
	switch_print(situation, "\nScore: %d\n", score);
}