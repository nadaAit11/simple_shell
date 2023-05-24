#include "shell.h"

/**
 * strcat_cd - function that concatenates the message for cd error.
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */

char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_Flag;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_Flag = malloc(3);
		illegal_Flag[0] = '-';
		illegal_Flag[1] = datash->args[1][1];
		illegal_Flag[2] = '\0';
		_strcat(error, illegal_Flag);
		free(illegal_Flag);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message for cd command in get_cd.
 * @datash: data relevant (directory)
 * Return: error message
 */

char *error_get_cd(data_shell *datash)
{
	int length, length_id;
	char *Error, *ver_str, *Msg;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		Msg = ": Illegal option ";
		length_id = 2;
	}
	else
	{
		Msg = ": can't cd to ";
		legth_id = _strlen(datash->args[1]);
	}

	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(ver_str) + _strlen(Msg) + length_id + 5;
	Error = malloc(sizeof(char) * (length + 1));

	if (Error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	Error = strcat_cd(datash, Msg, Error, ver_str);
	free(ver_str);

	return (Error);
}

/**
 * error_not_found - generic error message for command not found.
 * @datash: data relevant (counter, arguments).
 * Return: Error message
 */

char *error_not_found(data_shell *datash)
{
	int length;
	char *Error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + 16;
	Error = malloc(sizeof(char) * (length + 1));
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
	_strcat(Error, ": not found\n");
	_strcat(Error, "\0");
	free(ver_str);
	return (Error);
}

/**
 * error_exit_shell - generic error message for exit in get_exit.
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */

char *error_exit_shell(data_shell *datash)
{
	int length;
	char *Error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	Error = malloc(sizeof(char) * (length + 1));
	if (Error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(Error, datash->av[0]);
	_strcat(Error, ": ");
	_strcat(Error, ver_str);
	_strcat(Error, ": ");
	_strcat(Error, datash->args[0]);
	_strcat(Error, ": Illegal number: ");
	_strcat(Error, datash->args[1]);
	_strcat(Error, "\n\0");
	free(ver_str);

	return (Error);
}
