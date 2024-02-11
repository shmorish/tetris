#include "tetris.h"

// Time when the last move down process was executed
static struct timeval last_exec_time;
// Time when the last frame was printed
static struct timeval last_frame_time;

static suseconds_t get_time(struct timeval time)
{
	// 1sec = 1000000usec
	int sec2usec = 1000000;

	return (time.tv_sec * sec2usec + time.tv_usec);
}

void	init_time(void)
{
	gettimeofday(&last_exec_time, NULL);
	gettimeofday(&last_frame_time, NULL);
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

void print_output_according_to_fps(const t_player *player)
{
	struct timeval now;
	int sec2usec = 1000000; // 1sec = 1000000usec
	int time_to_next_frame;

	time_to_next_frame = sec2usec / FPS;
	gettimeofday(&now, NULL);
	if ((get_time(now) - get_time(last_frame_time)) > time_to_next_frame)
	{
		print_table(GAME_ON, player, player->table->score);
		gettimeofday(&last_frame_time, NULL);
	}
}
