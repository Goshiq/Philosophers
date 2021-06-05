#include "phil.h"

void	g_watcher(t_data *inp)
{
	while (inp->dead_id < -1)
	{
		pthread_mutex_lock(inp->count);
		if (inp->counter <= 0)
		{
			pthread_mutex_unlock(inp->count);
			break ;
		}
		pthread_mutex_unlock(inp->count);
		usleep(5);
	}
	if (inp->dead_id > -1)
	{
		pthread_mutex_lock(inp->m_write);
		printf(RED"%lu %d died\n",
			p_time() - inp->start, inp->dead_id + 1);
	}
}

int	create_env(t_data *inp, t_ph *phils)
{
	size_t		i;

	i = 0;
	pthread_mutex_init(inp->m_write, 0x0);
	pthread_mutex_init(inp->count, 0x0);
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
		if (inp->num_phil == 2)
			usleep(40);
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
	in->t_id = malloc(sizeof(pthread_t) * in->num_phil * 2);
	in->m_id = malloc(sizeof(pthread_mutex_t) * in->num_phil);
	in->m_write = malloc(sizeof(pthread_mutex_t));
	in->count = malloc(sizeof(pthread_mutex_t));
	phils = malloc(sizeof(t_ph) * in->num_phil);
	if (!in->t_id || !in->m_id || !in->m_write || !phils || !in->count)
		return (ft_err("Error: malloc error\n"));
	if (init_phil(in, phils) || create_env(in, phils))
		return (ft_err("Error: threads error\n"));
	g_watcher(in);
	free_all(in, phils);
	return (0);
}
