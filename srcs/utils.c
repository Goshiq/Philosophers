#include <phil.h>

size_t	p_time(void)
{
	struct timeval	what_time_is_it;

	gettimeofday(&what_time_is_it, 0x0);
	return (what_time_is_it.tv_sec * 1000 + what_time_is_it.tv_usec / 1000);
}
