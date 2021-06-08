#include "phil.h"

void	*l_watcher(void *ptr)
{
	t_ph	*ph;

	ph = (t_ph *)ptr;
	while (1)
	{
		sem_wait(ph->in->s_dead);
		if (p_time() > ph->time_to_die + 4)
		{
			sem_post(ph->in->s_dead);
			sem_wait(ph->in->s_count);
			if (ph->in->limit && ph->num_eat == ph->in->num_eat)
			{
				sem_post(ph->in->s_count);
				exit(0);
			}
			sem_post(ph->in->s_count);
			sem_wait(ph->in->s_write);
			put_alot(p_time() - ph->in->start, ph->id, " died\n");
			exit(0);
		}
		sem_post(ph->in->s_dead);
		usleep(50);
	}
	return (0x0);
}

void	life(t_ph *ph)
{
	pthread_t	t_dead;

	pthread_create(&t_dead, 0x0, l_watcher, (void *)ph);
	pthread_detach(t_dead);
	while (1)
	{
		p_eat(ph);
		sem_wait(ph->in->s_count);
		if (ph->in->limit && ph->num_eat == ph->in->num_eat)
		{
			sem_post(ph->in->s_count);
			exit(0);
		}
		sem_post(ph->in->s_count);
		p_sleep(ph);
		p_think(ph);
	}
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
	put_alot(p_time() - ph->in->start, ph->id, " is eating\n");
	sem_post(ph->in->s_write);
	sem_wait(ph->in->s_dead);
	ph->time_to_die = p_time() + ph->in->t_die / 1000;
	sem_post(ph->in->s_dead);
	usleep(ph->in->t_eat);
	sem_wait(ph->in->s_count);
	ph->num_eat++;
	sem_post(ph->in->s_count);
	sem_post(ph->in->s_id);
	sem_post(ph->in->s_id);
}

void	p_sleep(t_ph *ph)
{
	sem_wait(ph->in->s_write);
	put_alot(p_time() - ph->in->start, ph->id, " is sleeping\n");
	sem_post(ph->in->s_write);
	usleep(ph->in->t_sleep);
}

void	p_think(t_ph *ph)
{
	sem_wait(ph->in->s_write);
	put_alot(p_time() - ph->in->start, ph->id, " is thinking\n");
	sem_post(ph->in->s_write);
}
