#include "my_math.h"

int		check_overflow(size_t num, int i, int dig)
{
	if (i == num_len(SIZE_MAX) - 1)
	{
		if (num > SIZE_MAX / 10)
			return (1);
		if ((num == SIZE_MAX / 10) && (dig > (int)(SIZE_MAX % 10)))
			return (1);
	}
	return (0);
}

int		ft_atoi(size_t *num, char *str)
{
	int	i;

	i = 0;
	*num = 0;
	while (str[i])
	{
		if (ft_is_num(str[i]) && !check_overflow(*num, i, str[i] - 48))
			*num = *num * 10 + str[i++] - 48;
		else
			return (1);
	}
	return (0);
}

int		ft_is_num(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	num_len(size_t num)
{
	int	ans;

	ans = 1;
	while (num / 10)
	{
		ans++;
		num /= 10;
	}
	return (ans);
}
