#include "minitalk.h"
#include <stdint.h>
#include <stdlib.h>

void	ft_putstr(const char *str, int fd)
{
	if (NULL == str)
		return ;
	if (*str)
	{
		write(fd, str++, 1);
		ft_putstr(str, fd);
	}
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;

	sign = +1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13)
		|| *str == 32)
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
		{
			ft_putstr("Write a correct PID!\n", 2);
			exit(EXIT_FAILURE);
		}
		nbr = (nbr * 10) + (*str - 48);
		++str;
	}
	return (nbr * sign);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		if (n == INT32_MIN)
			ft_putstr("-2147483648", 1);
		n = -n;
	}
 if (n < 10)
	{
		c = n + 48;
		write(STDOUT_FILENO, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}
