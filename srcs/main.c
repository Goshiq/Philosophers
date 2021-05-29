#include "phil.h"

void	*do_eat(void *ptr)
{
	printf("%s\n", (char *)ptr);
	return 0x0;
}

int		main(int argc, char **argv)
{
	t_data		inp;
	pthread_t	*t_id;
	int			*ids;
	size_t		i;

	if (argc < 5 || argc > 6 || parse_it(&inp, argc, argv))
		return (ft_err("Error: argument\n"));
	if (!(t_id = malloc(sizeof(pthread_t) * inp.num_phil)) ||
			!(ids = malloc(sizeof(int) * inp.num_phil)) || 0 > inp.num_phil)
		return (ft_err("Error: malloc error\n"));
    printf("ids is %p\n", ids);
    printf("pthread is %p\n", t_id);
	printf("%lu\n", inp.num_phil);
	printf("%lu\n", inp.t_die);
	printf("%lu\n", inp.t_eat);
	printf("%lu\n", inp.t_sleep);
	printf("%lu\n", inp.num_eat);
	printf("%d\n", inp.limit);
	i = 0;
	while (i < inp.num_phil)
	{
		ids[i] = pthread_create(t_id + i, NULL, do_eat, (void *)"Hahaha");
		pthread_join(t_id[i], NULL);
		printf("return is: %d\n", ids[i]);
		i++;
	}
	i = 0;
	return (0);
}
