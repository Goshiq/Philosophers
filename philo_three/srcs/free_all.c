#include "phil.h"

void	free_all(t_data *in, t_ph *phils)
{
	size_t	i;

	i = 0;
	if (phils)
		free(phils);
	if (in)
	{
		sem_unlink("forks");
		sem_unlink("count");
		sem_unlink("dead");
		sem_unlink("write");
		free(in);
	}
}
