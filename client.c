#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * When server sends SIGUSR2 i know 
 * we have finished
*/
void	end(int sig)
{
	if (sig == SIGUSR2)
		ft_putstr("Message correctly received!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

/*
 * Send every char bit by bit
 * 	~SIGUSR1 -> 1
 * 	~SIGUSR2 -> 0
*/
void	send_char(char c, int server_pid)
{
	int	bit;

	bit = 0;
	while (bit <= 7)
	{
		if (c & (0b10000000 >> bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		++bit;
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	server_pid;

	signal(SIGUSR2, end);
	i = 0;
	server_pid = ft_atoi(av[1]);
	if (3 == ac)
	{
		while (av[2][i])
			send_char(av[2][i++], server_pid);
		send_char('\0', server_pid);
	}
	else
	{
		ft_putstr("Please enter the correct input"
			"./client <PID> \"Message\"\n", 2);
	}
}
