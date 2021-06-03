#include "phil.h"

void	*main_loop(void *ptr)
{
	t_data			*inp;
	size_t			i;

	inp = (t_data *)ptr;
	i = 0;
	while (i++ < inp->num_phil)
		printf("Id is: %ld\n", i - 1);
	i = 5;
	while (i > 0){
		printf("Exit in %ld\n", i--);
		usleep(1000000);
	}
	inp->dead_id = 0;
	return (0x0);
}

void	*watcher(void *ptr) {
	t_data	*inp;

	inp = (t_data *)ptr;
	while (inp->dead_id < -1)
		;
	if (inp->dead_id > -1)
	{
		printf("Phil #%d is dead\n", inp->dead_id);
		printf("Time is: %lu\n", p_time() - inp->start);
	}
	exit(1);
	return 0x0;
}

int	create_env(t_data *inp)
{
	size_t		i;
	pthread_t	w;
	t_ph		*phil;

	i = 0;
	if (pthread_create(&w, 0x0, watcher, (void *)inp) > 0)
		return (1);
	pthread_detach(w);
	phil = malloc(sizeof(t_ph) * inp->num_phil);
	if (!phil)
		ft_err("Error: malloc error\n");
	while (i < inp->num_phil)
	{
		pthread_mutex_init(inp->m_id + i, 0x0);
		if (pthread_create(inp->t_id + i, 0x0, main_loop, (void *)inp) > 0)
			return (1);
		pthread_detach(*(inp->t_id + i++));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*in;

	in = malloc(sizeof(t_data));
	if (!in)
		ft_err("Error: malloc error\n");
	if (argc < 5 || argc > 6 || parse_it(in, argc, argv))
		ft_err("Error: argument\n");
	in->t_id = malloc(sizeof(pthread_t) * in->num_phil);
	in->m_id = malloc(sizeof(pthread_mutex_t) * in->num_phil);
	if (!in->t_id || !in->m_id || 0 > in->num_phil)
		ft_err("Error: malloc error\n");
	if (create_env(in))
		ft_err("Error: treads error\n");
	while (1)
		;
	return (0);
}
