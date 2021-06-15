#include "phil.h"

int	init_sem(t_data *inp)
{
	sem_unlink("forks");
	inp->s_id = sem_open("forks", O_CREAT, 0777, inp->num_phil);
	sem_unlink("write");
	inp->s_write = sem_open("write", O_CREAT, 0777, 1);
	sem_unlink("dead");
	inp->s_dead = sem_open("dead", O_CREAT, 0777, 1);
	sem_unlink("count");
	inp->s_count = sem_open("count", O_CREAT, 0777, 1);
	if (inp->s_id == SEM_FAILED || inp->s_write == SEM_FAILED
		|| inp->s_dead == SEM_FAILED || inp->s_count == SEM_FAILED)
		return (1);
	return (0);
}

void	check_exit(t_data *inp)
{
	size_t	i;
	int		status;

	i = 0;
	status = 0;
	while (i < inp->num_phil)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			i = 0;
			while (i < inp->num_phil)
				kill(inp->pid_id[i++], SIGKILL);
		}
		i++;
	}
}

int	create_env(t_data *inp, t_ph *phils)
{
	size_t		i;

	if (init_sem(inp))
		return (1);
	i = 0;
	while (i < inp->num_phil)
	{
		inp->pid_id[i] = fork();
		if (inp->pid_id[i] == 0)
		{
			phils[i].id = i;
			life(phils + i);
		}
		else if (inp->pid_id[i] == -1)
			return (1);
		i++;
		usleep(100);
	}
	check_exit(inp);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*in;
	t_ph		*phils;

	in = malloc(sizeof(t_data));
	if (!in)
		return (ft_err("Error: malloc error\n"));
	if (argc < 5 || argc > 6 || parse_it(in, argc, argv))
		return (ft_err("Error: argument\n"));
	in->pid_id = malloc(sizeof(pid_t) * in->num_phil);
	phils = malloc(sizeof(t_ph) * in->num_phil);
	if (!in->pid_id || !phils)
		return (ft_err("Error: malloc error\n"));
	if (init_phil(in, phils) || create_env(in, phils))
		return (ft_err("Error: processes error\n"));
	free_all(in, phils);
	return (0);
}
