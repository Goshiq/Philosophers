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
	pthread_mutex_t	*m_write;
	size_t			start;
	int				dead_id;
}					t_data;

typedef struct		s_ph
{
	int				id;
	t_data			*in;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	size_t			time_to_die;
}					t_ph;

int		ft_err(char *str);
void	init_inp(t_data *inp);
int		init_phil(t_data *in, t_ph *phils);
int		parse_it (t_data *inp, int argc, char **argv);

#endif
