#include "phil.h"

void	*l_watcher(void *ptr)
{
	t_ph	*ph;

	ph = (t_ph *)ptr;
	while (1)
		if (p_time() > ph->time_to_die)
		{
			ph->in->dead_id = ph->id;
			break;
		}
	return (0x0);
}

void	*life(void *ptr)
{
	t_ph	*ph;

	ph = (t_ph *)ptr;
	if (pthread_create(ph->in->t_id + ph->id + ph->in->num_phil, 0x0,
				l_watcher, (void *)ph) > 0)
		ph->in->dead_id = ph->id;
	pthread_detach(*(ph->in->t_id + ph->id + ph->in->num_phil));
	p_eat(ph);
	p_sleep(ph);
	p_think(ph);
	return (0x0);
}

void	p_eat(t_ph *ph)
{
	pthread_mutex_lock(ph->left);
	pthread_mutex_lock(ph->in->m_write);
	printf("%lu %d has taken a fork\n", p_time() - ph->in->start, ph->id + 1);
	pthread_mutex_unlock(ph->in->m_write);
	pthread_mutex_lock(ph->right);
	pthread_mutex_lock(ph->in->m_write);
	printf("%lu %d has taken a fork\n", p_time() - ph->in->start, ph->id + 1);
	pthread_mutex_unlock(ph->in->m_write);
	ph->time_to_die = p_time() + ph->in->t_die;
	pthread_mutex_lock(ph->in->m_write);
	printf("%lu %d is eating\n", p_time() - ph->in->start, ph->id + 1);
	pthread_mutex_unlock(ph->in->m_write);
	usleep(ph->in->t_eat);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);

}

void	p_think(t_ph *ph)
{
	pthread_mutex_lock(ph->in->m_write);
	printf("%lu %d is thinking\n", p_time() - ph->in->start, ph->id + 1);
	pthread_mutex_unlock(ph->in->m_write);
}

void	p_sleep(t_ph *ph)
{
	pthread_mutex_lock(ph->in->m_write);
	printf("%lu %d is sleeping\n", p_time() - ph->in->start, ph->id + 1);
	usleep(ph->in->t_sleep);
	pthread_mutex_unlock(ph->in->m_write);
}
