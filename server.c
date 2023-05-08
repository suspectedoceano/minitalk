#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Problems with sigaction
*/
void	error_server(void)
{
	ft_putstr("Error with the server\n", 2);
	exit(EXIT_FAILURE);
}

/*
 * Take every bit from the most sig. one
 * recreating the char in toto
*/
void	handler(int sig, siginfo_t *info, void *more_info)
{
	static char	c = 0b00000000;
	static int	bit = 0;

	(void)more_info;
	if (SIGUSR1 == sig)
		c |= (0b10000000 >> bit);
	++bit;
	if (8 == bit)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
			write(1, &c, 1);
		c = 0b00000000;
		bit = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 1)
	{
		ft_putstr("Please enter only the ./server process"
			"name\n", 2);
		exit(EXIT_FAILURE);
	}
	av = NULL;
	ft_putstr("PID-> ", STDOUT_FILENO);
	ft_putnbr(getpid());
	write(STDOUT_FILENO, "\n", 1);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error_server();
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		error_server();
	while (1)
		pause();
}
