#include "shell.h"

/**
 * Copy_Info - Copies info to create.
 * a new env or alias.
 * @name: name
 * @value: value ( env or alias).
 * Return: new env or alias
 */

char *Copy_Info(char *name, char *value)
{
	char *new;
	int length_name, length_value, length;

	length_name = _strlen(name);
	length_value = _strlen(value);
	length = length_name + length_value + 2;
	new = malloc(sizeof(char) * (length));

	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * Set_Env - sets an environment variable.
 * @name: name of the environment variable.
 * @value: The value of the environment variable.
 * @datash: data structure (envrion).
 * Return: void
 */

void Set_Env(char *name, char *value, data_shell *datash)
{
	int i;
	char *var_envi, *name_envi;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_envi = _strdup(datash->_environ[i]);
		name_envi = _strtok(var_envi, "=");
		if (_strcmp(name_envi, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = Copy_Info(name_envi, value);
			free(var_envi);
			return;
		}
		free(var_envi);
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = Copy_Info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _Setenv - Compares env variables names.
 * with the name passed
 * @datash: data relevant (env's name and value)
 * Return: 1 on success
 */

int _Setenv(data_shell *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	Set_Env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _Unsetenv - Deletes an environment variable.
 * @datash: data relevant (env name).
 * Return: 1 on success.
 */

int _Unsetenv(data_shell *datash)
{
	char **realloc_env;
	char *var_envi, *name_envi;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_envi = _strdup(datash->_environ[i]);
		name_envi = _strtok(var_envi, "=");
		if (_strcmp(name_envi, datash->args[1]) == 0)
		{
			k = i;
		}
		free(var_envi);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_env;
	return (1);
}
