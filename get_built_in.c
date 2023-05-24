#include "shell.h"

/**
 * get_builtin - builtin that pais the command in the arg.
 * @cmd: command.
 *
 * Return: function pointer of the builtin command
 */

int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{"env", _Env},
		{"exit", exit_shell},
		{"setenv", _Setenv},
		{"unsetenv", _Unsetenv},
		{"cd", Cd_shell},
		{"help", get_help},
		{NULL, NULL}
	};
	int j;

	for (j = 0; builtin[j].name; j++)
	{
		if (_strcmp(builtin[j].name, cmd) == 0)
			break;
	}

	return (builtin[j].f);
}
