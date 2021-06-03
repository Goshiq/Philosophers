#ifndef PHIL_H
# define PHIL_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include "my_math.h"
# include "parser.h"
# include "utils.h"

typedef struct	s_ph
{
	t_data		*inp;
	pthread_t	*right;
	pthread_t	*left;
}				t_ph;

#endif
