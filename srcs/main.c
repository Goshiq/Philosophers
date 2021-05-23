#include "phil.h"

int	main(int argc, char **argv)
{
	t_data		inp;
	pthread_t	*t_id;

	if (argc < 5 || argc > 6 || parse_it(&inp, argc, argv))
		return (ft_err("Error: argument\n"));
	if (inp.num_phil && !(t_id = malloc(sizeof(pthread_t) * inp.num_phil)))
		return (ft_err("Error: malloc error\n"));
	printf("adr is %p\n", t_id);
	printf("%lu\n", inp.num_phil);
	printf("%lu\n", inp.t_die);
	printf("%lu\n", inp.t_eat);
	printf("%lu\n", inp.t_sleep);
	printf("%lu\n", inp.num_eat);
	printf("%d\n", inp.limit);
	do_it(inp, t_id);
}
