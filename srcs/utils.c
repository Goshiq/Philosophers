#include <phil.h>

size_t	p_time(void)
{
	struct timeval	what_time_is_it;

	gettimeofday(&what_time_is_it, 0x0);
	return (what_time_is_it.tv_sec * 1000 + what_time_is_it.tv_usec / 1000);
}

void	free_all(t_data *in, t_ph *phils)
{
	if (phils)
		free(phils);
	if (in)
	{
		if (in->m_write)
			free(in->m_write);
		if (in->m_id)
			free(in->m_id);
		if (in->t_id)
			free(in->t_id);
	}
}
