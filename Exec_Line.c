#include "shell.h"

/**
 * Exec_Line - Searches for built-in commands and external commands.
 * @datash: data relevant (args).
 *
 * Return: 1 on success
 */

int Exec_Line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (Cmd_Exec(datash));
}
