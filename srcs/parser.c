#include "parser.h"

void	ft_init(t_data *inp)
{
	inp->num_phil = 0;
	inp->t_die = 0;
	inp->t_eat = 0;
	inp->t_sleep = 0;
	inp->num_eat = 0;
	inp->limit = 0;
	inp->t_id = 0x0;
	inp->m_id = 0x0;
	inp->curr_id = -1;
}

int	parse_it(t_data *inp, int argc, char **argv)
{
	ft_init(inp);
	if (ft_atoi(&(inp->num_phil), argv[1]) || ft_atoi(&(inp->t_die), argv[2])
		|| ft_atoi(&(inp->t_eat), argv[3]) || ft_atoi(&(inp->t_sleep), argv[4]))
		return (1);
	if (argc == 6)
	{
		if (ft_atoi((&inp->num_eat), argv[5]))
			return (1);
		inp->limit = 1;
	}
	return (0);
}
