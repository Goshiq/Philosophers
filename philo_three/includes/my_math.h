#ifndef MY_MATH_H
# define MY_MATH_H

# include <stdint.h>
# include <stdio.h>

int	check_overflow(size_t num, int i, int dig);
int	ft_atoi(size_t *num, char *str);
int	ft_is_num(char c);
int	num_len(size_t num);

#endif
