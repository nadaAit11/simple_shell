#include "shell.h"

/**
 * get_sigint - handle the ctrl + c call in prompt
 * @sig: signal handler
 */

void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^,- ", 5);
}
