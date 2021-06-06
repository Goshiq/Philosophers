#ifndef PARSER_H
# define PARSER_H

# include <pthread.h>

# define RED  "\x1b[31m"
# define GREEN  "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE  "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN  "\x1b[36m"
# define RESET  "\x1b[0m"

typedef struct s_data
{
	size_t			num_phil;
	size_t			counter;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			num_eat;
	int				limit;
	pthread_t		*t_id;
	sem_t			*s_id;
	sem_t			*s_write;
	sem_t			*s_dead;
	sem_t			*s_count;
	size_t			start;
	int				dead_id;
}	t_data;

typedef struct s_ph
{
	size_t			id;
	t_data			*in;
	size_t			time_to_die;
	size_t			num_eat;
}	t_ph;

int		ft_err(char *str);
void	init_inp(t_data *inp);
int		init_phil(t_data *in, t_ph *phils);
int		parse_it (t_data *inp, int argc, char **argv);

#endif
