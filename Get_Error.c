#include "shell.h"

/**
 * get_error - calls the error accoding the builtin, sysntax or permission.
 * @datash: data structure that contains arguments.
 * @eval: error value.
 *
 * Return: error
 */

int get_error(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
		case -1:
			error = Error_Env(datash);
			break;
		case 126:
			error = Error_Path_126(datash);
			break;
		case 127:
			error = Error_Not_Found(datash);
			break;
		case 2:
			if (_strcmp("exit", datash->args[0]) == 0)
				error = Error_Exit_Shell(datash);
			else if (_strcmp("cd", datash->args[0]) == 0)
				error = Error_Get_Cd(datash);
			break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
