#include "shell.h"

/**
 * exit_shell - exits the shell.
 * @datash: data relevant (status and args)
 *
 * Return: 0 on success.
 */

int exit_shell(data_shell *datash)
{
	unsigned int stat;
	int IS_digit;
	int str_LEN;
	int BIG_number;

	if (datash->args[1] != NULL)
	{
		stat = _atoi(datash->args[1]);
		IS_digit = _isdigit(datash->args[1]);
		str_LEN = _strlen(datash->args[1]);
		BIG_number = stat > (unsigned int)INT_MAX;
		if (!IS_digit || str_LEN > 10 || BIG_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (stat % 256);
	}
	return (0);
}
