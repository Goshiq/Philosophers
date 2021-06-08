#include "phil.h"

void	*l_watcher(void *ptr)
{
	t_ph	*ph;

	ph = (t_ph *)ptr;
	while (1)
	{
		if (p_time() > ph->time_to_die)
		{
			ph->in->dead_id = ph->id;
			break ;
		}
	}
	return (0x0);
}

void	*life(void *ptr)
{
	t_ph	*ph;

	ph = (t_ph *)ptr;
	while (1)
	{
		p_eat(ph);
		pthread_mutex_lock(ph->in->count);
		if (ph->in->limit && ph->num_eat == ph->in->num_eat)
		{
			ph->in->counter--;
			pthread_mutex_unlock(ph->in->count);
			break ;
		}
		pthread_mutex_unlock(ph->in->count);
		p_sleep(ph);
		p_think(ph);
		usleep(100);
	}
	return (0x0);
}

void	p_eat(t_ph *ph)
{
	pthread_mutex_lock(ph->right);
	pthread_mutex_lock(ph->in->m_write);
	put_alot(p_time() - ph->in->start, ph->id, " has taken a fork\n");
	pthread_mutex_unlock(ph->in->m_write);
	pthread_mutex_lock(ph->left);
	pthread_mutex_lock(ph->in->m_write);
	put_alot(p_time() - ph->in->start, ph->id, " has taken a fork\n");
	pthread_mutex_unlock(ph->in->m_write);
	pthread_mutex_lock(ph->in->m_write);
	put_alot(p_time() - ph->in->start, ph->id, " is eating\n");
	pthread_mutex_unlock(ph->in->m_write);
	pthread_mutex_lock(ph->in->m_dead);
	ph->time_to_die = p_time() + ph->in->t_die / 1000;
	pthread_mutex_unlock(ph->in->m_dead);
	usleep(ph->in->t_eat);
	pthread_mutex_lock(ph->in->count);
	ph->num_eat++;
	pthread_mutex_unlock(ph->in->count);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
}

void	p_think(t_ph *ph)
{
	pthread_mutex_lock(ph->in->m_write);
	put_alot(p_time() - ph->in->start, ph->id, " is thinking\n");
	pthread_mutex_unlock(ph->in->m_write);
}

void	p_sleep(t_ph *ph)
{
	pthread_mutex_lock(ph->in->m_write);
	put_alot(p_time() - ph->in->start, ph->id, " is sleeping\n");
	pthread_mutex_unlock(ph->in->m_write);
	usleep(ph->in->t_sleep);
}
