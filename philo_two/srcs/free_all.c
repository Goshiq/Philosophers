#include "phil.h"

void	free_all(t_data *in, t_ph *phils)
{
	size_t	i;

	i = 0;
	if (phils)
		free(phils);
	if (in)
	{
		if (in->t_id)
			free(in->t_id);
		free(in);
	}
}
