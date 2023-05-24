#include "shell.h"

/**
 * Error_Env - Error message for the 'get_env' function when encountering
 * issues with environment variables.
 *
 * @datash: data relevant (counter, arguments).
 * Return: error message
 */

char *Error_Env(data_shell *datash)
{
	int Length;
	char *Error;
	char *ver_str;
	char *Msg;

	ver_str = aux_itoa(datash->counter);
	Msg = ": Unable to add/remove from environment.\n";
	Length = _strlen(datash->av[0]) + _strlen(ver_str);
	Length += _strlen(datash->args[0]) + _strlen(Msg) + 4;
	Error = malloc(sizeof(char) * (Length + 1));
	if (Error == 0)
	{
		free(Error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(Error, datash->av[0]);
	_strcat(Error, ": ");
	_strcat(Error, ver_str);
	_strcat(Error, ": ");
	_strcat(Error, datash->args[0]);
	_strcat(Error, Msg);
	_strcat(Error, "\0");
	free(ver_str);

	return (Error);
}

/**
 * Error_Path_126 - Error message for path and failures and permission denied
 * errors.
 *
 * @datash: data relevant (counter, arguments)
 * Return: The error string
 */

char *Error_Path_126(data_shell *datash)
{
	int Length;
	char *ver_str;
	char *Error;

	ver_str = aux_itoa(datash->counter);
	Length = _strlen(datash->av[0]) + _strlen(ver_str);
	Length += _strlen(datash->args[0]) + 24;
	Error = malloc(sizeof(char) * (Length + 1));
	if (Error == 0)
	{
		free(Error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(Error, datash->av[0]);
	_strcat(Error, ": ");
	_strcat(Error, ver_str);
	_strcat(Error, ": ");
	_strcat(Error, datash->args[0]);
	_strcat(Error, ": Permission denied\n");
	_strcat(Error, "\0");
	free(ver_str);
	return (Error);
}
