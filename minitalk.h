#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>

#define BUSY	0
#define READY	1

void	Signal(int sig, void *handler, bool use_siginfo);
void	Kill(pid_t pid, int signum);

#endif
