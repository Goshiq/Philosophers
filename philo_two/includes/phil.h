#ifndef PHIL_H
# define PHIL_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include "parser.h"
# include "my_math.h"
# include "utils.h"

void	p_eat(t_ph *ptr);
void	*life(void *ptr);
void	*l_watcher(void *ptr);
void	p_think(t_ph *ptr);
void	p_sleep(t_ph *ptr);

#endif
