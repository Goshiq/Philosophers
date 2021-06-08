#include "phil.h"

void	g_watcher(t_data *inp, t_ph *phils)
{
	static size_t	i[2];

	while (!i[1])
	{
		if (inp->counter <= 0)
			break ;
		i[0] = 0;
		while (i[0]++ < inp->num_phil)
		{
			sem_wait(inp->s_dead);
			if (p_time() > phils[i[0] - 1].time_to_die + 4)
			{
				sem_post(inp->s_dead);
				if (inp->limit && phils[i[0] - 1].num_eat == inp->num_eat)
					continue ;
				sem_wait(inp->s_write);
				put_alot(p_time() - inp->start, phils[i[0] - 1].id, " died\n");
				return ;
			}
			sem_post(inp->s_dead);
		}
		usleep(100);
	}
}

int	init_sem(t_data *inp)
{
	sem_unlink("forks");
	inp->s_id = sem_open("forks", O_CREAT, 0777, inp->num_phil);
	sem_unlink("write");
	inp->s_write = sem_open("write", O_CREAT, 0777, 1);
	sem_unlink("count");
	inp->s_count = sem_open("count", O_CREAT, 0777, 1);
	sem_unlink("dead");
	inp->s_dead = sem_open("dead", O_CREAT, 0777, 1);
	if (inp->s_id == SEM_FAILED || inp->s_write == SEM_FAILED
		|| inp->s_dead == SEM_FAILED || inp->s_count == SEM_FAILED)
		return (1);
	return (0);
}

int	create_env(t_data *inp, t_ph *phils)
{
	size_t		i;

	if (init_sem(inp))
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
	phils = malloc(sizeof(t_ph) * in->num_phil);
	if (!in->t_id || !phils)
		return (ft_err("Error: malloc error\n"));
	if (init_phil(in, phils) || create_env(in, phils))
		return (ft_err("Error: threads error\n"));
	g_watcher(in, phils);
	free_all(in, phils);
	return (0);
}
