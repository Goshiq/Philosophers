#include "phil.h"

void	g_watcher(t_data *inp)
{
	while (inp->dead_id < -1)
		;
	if (inp->dead_id > -1)
	{
		pthread_mutex_lock(inp->m_write);
		printf("%lu %d died\n",
				p_time() - inp->start, inp->dead_id + 1);
	}
}

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
    printf("id is %d\nptr is %p\n", ph->id, ph->in->t_id + ph->id + ph->in->num_phil);
	ph->time_to_die = p_time() + ph->in->t_die;
	if (pthread_create(ph->in->t_id + ph->id + ph->in->num_phil, 0x0,
				l_watcher, (void *)ph) > 0)
        ph->in->dead_id = ph->id;
//	pthread_mutex_lock(ph->left);
//	pthread_mutex_lock(ph->right);
//	usleep(500);
//	pthread_mutex_unlock(ph->right);
//	pthread_mutex_unlock(ph->left);
	return (0x0);
}

int	create_env(t_data *inp, t_ph *phils)
{
	size_t		i;

	i = 0;
	pthread_mutex_init(inp->m_write, 0x0);
	while (i < inp->num_phil)
	{
		pthread_mutex_init(&(inp->m_id[i]), 0x0);
		if (pthread_create(&(inp->t_id[i]), 0x0, life, (void *)(phils + i)) > 0)
			return (1);
		pthread_detach(inp->t_id[i]);
		i++;
		if (inp->num_phil == 2)
			usleep(10);
    }
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*in;
	t_ph		*phils;

	in = malloc(sizeof(t_data));
	if (!in)
		return(ft_err("Error: malloc error\n"));
	if (argc < 5 || argc > 6 || parse_it(in, argc, argv))
		return(ft_err("Error: argument\n"));
	in->t_id = malloc(sizeof(pthread_t) * in->num_phil * 2);
	in->m_id = malloc(sizeof(pthread_mutex_t) * in->num_phil);
	in->m_write = malloc(sizeof(pthread_mutex_t));
	phils = malloc(sizeof(t_ph) * in->num_phil);
	if (!in->t_id || !in->m_id || !in->m_write || !phils)
		return(ft_err("Error: malloc error\n"));
    if (init_phil(in, phils) || create_env(in, phils)) {
        return(ft_err("Error: treads error\n"));
    }
    g_watcher(in);
    free_all(in, phils);
	return (0);
}
