#include "phil.h"

void	free_all(t_data *in, t_ph *phils)
{
	size_t	i;

	i = 0;
	if (phils)
		free(phils);
	if (in)
	{
		while (i < in->num_phil)
			pthread_mutex_destroy(in->m_id + i++);
		pthread_mutex_destroy(in->m_dead);
		pthread_mutex_destroy(in->count);
		pthread_mutex_destroy(in->m_write);
		if (in->m_id)
			free(in->m_id);
		if (in->t_id)
			free(in->t_id);
		if (in->m_write)
			free(in->m_write);
		free(in);
	}
}
