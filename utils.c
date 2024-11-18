#include "minitalk.h"

/**
 * Signal - Sets up signal handler with optional siginfo support
 * @sig: Signal to handle
 * @handler: Signal handler function (void* to support both types)
 * @use_siginfo: Boolean to determine if siginfo is needed
 */
void	Signal(int sig, void *handler, bool use_siginfo)
{
	struct sigaction	sa = {0};

	if (use_siginfo)
	{
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
	}
	else
		sa.sa_handler = handler;
 
	/* Block both signals during handler execution */
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
    
	if (sigaction(sig, &sa, NULL) < 0)
	{
		perror("Signal handler setup failed");
		exit(EXIT_FAILURE);
	}
}

/**
 * Kill - Wrapper for kill system call with error handling
 * @pid: Process ID to send signal to
 * @signum: Signal number to send
 */
void	Kill(pid_t pid, int signum)
{
	if (kill(pid, signum) < 0)
	{
		perror("Signal transmission failed");
		exit(EXIT_FAILURE);
	}
}


void print_pending_signals()
{
    sigset_t pending;
    if (sigpending(&pending) == -1) {
        perror("sigpending");
        exit(EXIT_FAILURE);
    }

    printf("\n=== Pending Signals ===\n");
    for (int i = 1; i < NSIG; i++) {
        if (sigismember(&pending, i)) {
            printf("Signal %d (%s) is pending\n", i, strsignal(i));
        }
    }
    printf("=======================\n\n");
}

// Function to print the list of blocked signals
void print_blocked_signals()
{
    sigset_t blocked;
    if (sigprocmask(SIG_BLOCK, NULL, &blocked) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("\n=== Blocked Signals ===\n");
    for (int i = 1; i < NSIG; i++) {
        if (sigismember(&blocked, i)) {
            printf("Signal %d (%s) is blocked\n", i, strsignal(i));
        }
    }
    printf("=======================\n");
}

