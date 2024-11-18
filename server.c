#include "minitalk.h"

/**
 * handler - Processes incoming signals to reconstruct characters
 * @sig: Signal type (SIGUSR1 or SIGUSR2)
 * @info: Signal information containing sender's PID
 * @more_info: Additional context (unused)
 * Note: Uses static variables to maintain state between signal calls
 */
static void	handler(int sig, siginfo_t *info, void *more_info)
{
	static char		c = 0;
	static int		bit = 0;
	static pid_t	goku = 0;


	/* Store client PID only once per connection */
	if (info->si_pid) 
		goku = info->si_pid;

	/* Build character bit by bit (MSB first) */
	if (SIGUSR1 == sig)
		c |= (0b10000000 >> bit);
	else if (SIGUSR2 == sig)
		c &= ~(0x80 >> bit);
	bit++;

	/* Process complete character */
	if (CHAR_BIT == bit)
	{
		bit = 0;
		if ('\0' == c)
		{
			write(STDOUT_FILENO, "\n", 1);
			Kill(goku, SIGUSR2);
			c = 0;
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
	Kill(goku, SIGUSR1);
}

/**
 * main - Server entry point
 * @ac: Argument count (must be 1)
 * @av: Argument vector (unused)
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int	main(int ac, char **av)
{

	if (ac != 1)
	{
		fputs("Usage: ./server\n", stderr);
		return (EXIT_FAILURE);
	}
	
	printf("Server PID: %d\n", getpid());

	/* Set up signal handlers with siginfo enabled */
	Signal(SIGUSR1, handler, true);
	Signal(SIGUSR2, handler, true);

	while (1337)
		pause();
		
	return (EXIT_SUCCESS);
}
