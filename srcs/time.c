#include "tetris.h"

// Time when the last move down process was executed
static struct timeval last_exec_time;

static suseconds_t get_time(struct timeval time)
{
	// 1sec = 1000000usec
	int sec2usec = 1000000;

	return (time.tv_sec * sec2usec + time.tv_usec);
}

void	init_time(void)
{
	gettimeofday(&last_exec_time, NULL);
}

bool time_elapsed(t_table *table)
{
	struct timeval now;
	int elapsed_time;

	gettimeofday(&now, NULL);
	elapsed_time = get_time(now) - get_time(last_exec_time);
	return (elapsed_time > table->time_to_execute);
}

void update_exec_time(void)
{
	gettimeofday(&last_exec_time, NULL);
}