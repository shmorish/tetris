#include "tetris.h"

// Time when the last move down process was executed
static struct timeval last_exec_time;
// Time when the last frame was drawn
static struct timeval last_frame_time;

static suseconds_t get_time(struct timeval time)
{
	int sec2usec = 1000000; // 1sec = 1000000usec

	return (time.tv_sec * sec2usec + time.tv_usec);
}

void update_exec_time(void)
{
	gettimeofday(&last_exec_time, NULL);
}

bool time_elapsed(t_tetris *tetris)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (get_time(now) - get_time(last_exec_time)) > tetris->time_to_execute;
}

void	init_time(void)
{
	gettimeofday(&last_exec_time, NULL);
	gettimeofday(&last_frame_time, NULL);
}

void print_output_according_to_fps(const t_tetris *tetris)
{
	struct timeval now;
	int sec2usec = 1000000; // 1sec = 1000000usec
	int time_to_next_frame;

	time_to_next_frame = sec2usec / FPS;
	gettimeofday(&now, NULL);
	if ((get_time(now) - get_time(last_frame_time)) > time_to_next_frame)
	{
		print_table(GAME_ON, tetris, tetris->score);
		gettimeofday(&last_frame_time, NULL);
	}
}