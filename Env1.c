#include "shell.h"

/**
 * Cmp_Env_Name - Performs a comparison of environment variable names.
 * with the name passed
 * @nenv: name og the environment variable
 * @name: name  passed.
 *
 * Return: 0 if are not equal, a value if they are
 */

int Cmp_Env_Name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _Getenv - Retrieve the value of an environment vriable.
 * @name: name of the environment variable.
 * @_environ: environment variable.
 *
 * Return: The value of the environment variable if it is found.
 * in other cases, return NULL
 */

char *_Getenv(const char *name, char **_environ)
{
	char *ptr_envi;
	int i, mv;

	/* Initialize ptr_env value */
	ptr_envi = NULL;
	mv = 0;
	/* Compare all environment variable */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* if name en env are equal */
		mv = Cmp_Env_Name(_environ[i], name);
		if (mv)
		{
			ptr_envi = _environ[i];
			break;
		}
	}

	return (ptr_envi + mv);
}

/**
 * _Env - Display the environment variables.
 *@datash: data relevant
 *
 * Return: 1 on success
 */

int _Env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{
		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
