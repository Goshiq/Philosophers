#include "phil.h"

int		ft_atoi(size_t *num, char *str)
{
	int	i;

	i = 0;
	*num = 0;
	while (str[i])
	{
		if (ft_is_num(str[i]))
			*num = *num * 10 + str[i++] - 48;
		else
			return (1);
	}
	return (0);
}

void	ft_init(t_data *inp)
{
	inp->num_phil = 0;
	inp->t_die = 0;
	inp->t_eat = 0;
	inp->t_sleep = 0;
	inp->num_eat = 0;
}

int		ft_is_num(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int		parse_it(t_data *inp, int argc, char **argv)
{
	ft_init(inp);
	if (ft_atoi(&(inp->num_phil), argv[1]) || ft_atoi(&(inp->t_die), argv[2])
		|| ft_atoi(&(inp->t_eat), argv[3]) || ft_atoi(&(inp->t_sleep), argv[4]))
		return (1);
	if (argc == 6)
		if (ft_atoi((&inp->num_eat), argv[5]))
			return (1);
	return (0);
}
