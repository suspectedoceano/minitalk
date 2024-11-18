#include "minitalk.h"

/* Global flag for synchronization between client and server */
volatile sig_atomic_t	g_kingKai = BUSY;

/**
 * end_handler - Handles server's completion signal
 * @sig: Signal number (unused)
 */
static void	end_handler(int sig)
{
	fputs("\n\t✅ Message received ✅\n", stdout);
	exit(EXIT_SUCCESS);
}

/**
 * ack_handler - Handles server's acknowledgment signals
 * @sig: Signal number (unused)
 */
static void	ack_handler(int sig)
{
	g_kingKai = READY;
}

/**
 * send_char - Sends a character bit by bit to server
 * @c: Character to send
 * @kingKai: Server's process ID
 */
static void	send_char(char c, pid_t kingKai)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{

		/* Send SIGUSR1 for 1, SIGUSR2 for 0 */
		if (c & (0x80 >> bit))
			Kill(kingKai, SIGUSR1);
		else
			Kill(kingKai, SIGUSR2);
		bit++;

		/* Wait for server acknowledgment */
		while (BUSY == g_kingKai)
			usleep(42);

		// 🧊
		g_kingKai = BUSY;
	}
}

/**
 * main - Client entry point
 * @ac: Argument count (must be 3)
 * @av: Arguments (PID and message)
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int	main(int ac, char **av)
{
	pid_t	kingKai;
	char	*message;
	int		i;

	if (ac != 3)
	{
		fputs("Usage: ./client <kingKai> \"message\"\n", stderr);
		return (EXIT_FAILURE);
	}
	kingKai = atoi(av[1]);
	message = av[2];

	/* Set up signal handlers without siginfo */
	Signal(SIGUSR1, ack_handler, false);
	Signal(SIGUSR2, end_handler, false);

	i = 0;
	while (message[i])
		send_char(message[i++], kingKai);
	send_char('\0', kingKai);

	return (EXIT_SUCCESS);
}

