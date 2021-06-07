#include "phil.h"

void	g_watcher(t_data *inp, t_ph *phils)
{
	size_t	i;

	while (1)
	{
		pthread_mutex_lock(inp->count);
		if (inp->counter <= 0)
			break ;
		pthread_mutex_unlock(inp->count);
		i = 0;
		while (i++ < inp->num_phil)
		{
			pthread_mutex_lock(inp->m_dead);
			if (p_time() > phils[i - 1].time_to_die + 4)
			{
				pthread_mutex_unlock(inp->m_dead);
				if (inp->limit && phils[i - 1].num_eat == inp->num_eat)
					continue ;
				pthread_mutex_lock(inp->m_write);
				put_alot(p_time() - inp->start, phils[i - 1].id, " died\n");
				return ;
			}
			pthread_mutex_unlock(inp->m_dead);
		}
		usleep(100);
	}
}

int	create_env(t_data *inp, t_ph *phils)
{
	size_t		i;

	i = 0;
	if (pthread_mutex_init(inp->m_write, 0x0) || \
			pthread_mutex_init(inp->m_dead, 0x0) || \
			pthread_mutex_init(inp->count, 0x0))
		return (1);
	while (i < inp->num_phil)
		if (pthread_mutex_init(inp->m_id + i++, 0x0) > 0)
			return (1);
	i = 0;
	while (i < inp->num_phil)
	{
		if (pthread_create(inp->t_id + i, 0x0, life, (void *)&phils[i]) > 0)
			return (1);
		pthread_detach(inp->t_id[i]);
		i++;
		usleep(50);
	}
	i = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*in;
	t_ph		*phils;

	in = malloc(sizeof(t_data));
	if (!in)
		return (ft_err("Error: malloc error\n"));
	if (argc < 5 || argc > 6 || parse_it(in, argc, argv))
		return (ft_err("Error: argument\n"));
	in->t_id = malloc(sizeof(pthread_t) * in->num_phil);
	in->m_id = malloc(sizeof(pthread_mutex_t) * in->num_phil);
	in->m_write = malloc(sizeof(pthread_mutex_t));
	in->m_dead = malloc(sizeof(pthread_mutex_t));
	in->count = malloc(sizeof(pthread_mutex_t));
	phils = malloc(sizeof(t_ph) * in->num_phil);
	if (!in->t_id || !in->m_id || !in->m_write || !phils || !in->count)
		return (ft_err("Error: malloc error\n"));
	if (init_phil(in, phils) || create_env(in, phils))
		return (ft_err("Error: threads error\n"));
	g_watcher(in, phils);
	usleep(1000);
	free_all(in, phils);
	return (0);
}
