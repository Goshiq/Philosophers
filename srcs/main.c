#include "phil.h"

void	*main_loop(void *ptr)
{
	t_data			*inp;
	size_t			i;

	inp = (t_data *)ptr;
	i = 0;
//	pthread_mutex_lock(inp->m_id + inp->curr_id);
	pthread_mutex_lock(inp->m_id);
	while (i++ < 10)
		printf("Id is: %d\n", inp->curr_id);
	pthread_mutex_unlock(inp->m_id);
	return (0x0);
}

int	create_env(t_data *inp)
{
	size_t	i;

	i = 0;
	while (i < inp->num_phil)
	{
		inp->curr_id = i;
		pthread_mutex_init(inp->m_id + i, 0x0);
		if (pthread_create(inp->t_id + i, 0x0, main_loop, (void *)inp) > 0)
			return (1);
		pthread_join(*(inp->t_id + i++), 0x0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*in;

	in = malloc(sizeof(t_data));
	if (!in)
		return (ft_err("Error: malloc error\n"));
	if (argc < 5 || argc > 6 || parse_it(in, argc, argv))
		return (ft_err("Error: argument\n"));
	in->t_id = malloc(sizeof(pthread_t) * in->num_phil);
	in->m_id = malloc(sizeof(pthread_mutex_t) * in->num_phil);
	if (!in->t_id || !in->m_id || 0 > in->num_phil)
		return (ft_err("Error: malloc error\n"));
	if (create_env(in))
		return (ft_err("Error: treads error\n"));
	return (0);
}
