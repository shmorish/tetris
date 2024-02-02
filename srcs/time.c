#include "tetris.h"

static struct timeval last_exec_time;

static suseconds_t get_time(struct timeval time)
{
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void update_exec_time(void)
{
	gettimeofday(&last_exec_time, NULL);
}

int time_elapses(t_tetris *tetris)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (get_time(now) - get_time(last_exec_time)) > tetris->time_to_execute;
}
