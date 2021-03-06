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
		if (ph->in->limit && ph->num_eat == ph->in->num_eat)
		{
			sem_wait(ph->in->s_count);
			ph->in->counter--;
			sem_post(ph->in->s_count);
			break ;
		}
		p_sleep(ph);
		p_think(ph);
	}
	return (0x0);
}

void	p_eat(t_ph *ph)
{
	sem_wait(ph->in->s_id);
	sem_wait(ph->in->s_write);
	put_alot(p_time() - ph->in->start, ph->id, " has taken a fork\n");
	sem_post(ph->in->s_write);
	sem_wait(ph->in->s_id);
	sem_wait(ph->in->s_write);
	put_alot(p_time() - ph->in->start, ph->id, " has taken a fork\n");
	sem_post(ph->in->s_write);
	sem_wait(ph->in->s_write);
	put_alot(p_time() - ph->in->start, ph->id, " is eating\n");
	sem_post(ph->in->s_write);
	sem_wait(ph->in->s_dead);
	ph->time_to_die = p_time() + ph->in->t_die / 1000;
	sem_post(ph->in->s_dead);
	usleep(ph->in->t_eat);
	ph->num_eat++;
	sem_post(ph->in->s_id);
	sem_post(ph->in->s_id);
}

void	p_think(t_ph *ph)
{
	sem_wait(ph->in->s_write);
	put_alot(p_time() - ph->in->start, ph->id, " is thinking\n");
	sem_post(ph->in->s_write);
}

void	p_sleep(t_ph *ph)
{
	sem_wait(ph->in->s_write);
	put_alot(p_time() - ph->in->start, ph->id, " is sleeping\n");
	sem_post(ph->in->s_write);
	usleep(ph->in->t_sleep);
}
