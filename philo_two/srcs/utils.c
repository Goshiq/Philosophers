#include <phil.h>

size_t	p_time(void)
{
	struct timeval	what_time_is_it;

	gettimeofday(&what_time_is_it, 0x0);
	return (what_time_is_it.tv_sec * 1000 + what_time_is_it.tv_usec / 1000);
}

void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	put_alot(size_t n1, size_t n2, char *str)
{
	putnum(n1);
	putstr(" ");
	putnum(n2 + 1);
	putstr(str);
}

size_t	my_pow(int i)
{
	size_t	ans;

	ans = 1;
	while (i-- > 1)
		ans *= 10;
	return (ans);
}

void	putnum(size_t num)
{
	char	c;
	int		i;
	size_t	div;

	i = num_len(num);
	while (i-- > 0)
	{
		div = my_pow(i + 1);
		c = num / div + 48;
		write(1, &c, 1);
		num %= div;
	}
}
