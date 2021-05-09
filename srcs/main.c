#include "phil.h"

int	main(int argc, char **argv)
{
	t_data	inp;

	if (argc < 5 || argc > 6 || parse_it(&inp, argc, argv))
		return (ft_err("Error: argument\n"));
	printf("%lu\n", inp.num_phil);
	printf("%lu\n", inp.t_die);
	printf("%lu\n", inp.t_eat);
	printf("%lu\n", inp.t_sleep);
	printf("%lu\n", inp.num_eat);
}
