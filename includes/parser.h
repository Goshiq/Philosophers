#ifndef PARSER_H
# define PARSER_H

# include <pthread.h>

typedef struct		s_data
{
	size_t			num_phil;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			num_eat;
	int				limit;
	pthread_t		*t_id;
	pthread_mutex_t	*m_id;
	size_t			start;
	int				dead_id;
}					t_data;

void	ft_err(char *str);
void	ft_init(t_data *inp);
int		parse_it (t_data *inp, int argc, char **argv);

#endif
