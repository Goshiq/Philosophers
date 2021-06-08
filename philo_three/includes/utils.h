#ifndef UTILS_H
# define UTILS_H

# include <sys/time.h>
# include <unistd.h>
# include "phil.h"

void	free_all(t_data *in, t_ph *phils);
size_t	p_time(void);
void	put_alot(size_t n1, size_t n2, char *str);
void	putnum(size_t num);
void	putstr(char *str);

#endif
