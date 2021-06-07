#include "phil.h"

void	init_inp(t_data *inp)
{
	inp->num_phil = 0;
	inp->counter = 0;
	inp->t_die = 0;
	inp->t_eat = 0;
	inp->t_sleep = 0;
	inp->num_eat = -1;
	inp->limit = 0;
	inp->t_id = 0x0;
	inp->m_id = 0x0;
	inp->m_write = 0x0;
	inp->m_dead = 0x0;
	inp->count = 0x0;
	inp->start = p_time();
	inp->dead_id = -2;
}

int	init_phil(t_data *in, t_ph *phils)
{
	size_t	i;

	i = 0;
	while (i < in->num_phil)
	{
		phils[i].id = i;
		phils[i].in = in;
		phils[i].right = in->m_id + i;
		phils[i].left = in->m_id + (i + 1) % in->num_phil;
		phils[i].time_to_die = p_time() + in->t_die;
		phils[i].num_eat = 0;
		i++;
	}
	return (0);
}

int	parse_it(t_data *inp, int argc, char **argv)
{
	init_inp(inp);
	if (ft_atoi(&(inp->num_phil), argv[1]) || ft_atoi(&(inp->t_die), argv[2])
		|| ft_atoi(&(inp->t_eat), argv[3]) || ft_atoi(&(inp->t_sleep), argv[4]))
		return (1);
	inp->counter = inp->num_phil;
	inp->t_die *= 1000;
	inp->t_eat *= 1000;
	inp->t_sleep *= 1000;
	if (argc == 6)
	{
		if (ft_atoi((&inp->num_eat), argv[5]))
			return (1);
		if (!inp->limit)
			return (1);
		inp->limit = 1;
	}
	if (inp->num_phil < 2)
		return (1);
	return (0);
}
