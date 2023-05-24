#include "shell.h"

/**
 * is_cdir - checks ":" is in the current directory or not
 * @path: type char pointer char
 * @i: type int pointer of index
 * Return: 1 if the path is searchable in the cd, 0 otherwise
 */

int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a command
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command
 */

char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *direc;
	int leng_dir, leng_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		leng_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			leng_dir = _strlen(token_path);
			direc = malloc(leng_dir + leng_cmd + 2);
			_strcpy(direc, token_path);
			_strcat(direc, "/");
			_strcat(direc, cmd);
			_strcat(direc, "\0");
			if (stat(direc, &st) == 0)
			{
				free(ptr_path);
				return (direc);
			}
			free(direc);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if it is an executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable, other number if it does
 */

int is_executable(data_shell *datash)
{
	struct stat sta;
	int j;
	char *input;

	input = datash->args[0];
	for (j = 0; input[j]; j++)
	{
		if (input[j] == '.')
		{
			if (input[j + 1] == '.')
				return (0);
			if (input[j + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[j] == '/' && j != 0)
		{
			if (input[j + 1] == '.')
				continue;
			j++;
			break;
		}
		else
			break;
	}
	if (j == 0)
		return (0);

	if (stat(input + j, &sta) == 0)
		return (j);

	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if the user has permissions to access
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */

int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * cmd_exec - executes command lines
 * @datash: data relevant (args and input)
 * Return: 1 on success
 */

int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int stat;
	int exe;
	char *dire;
	(void) wpd;

	exe = is_executable(datash);
	if (exe == 0)
	{
		dire = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(dire, datash) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exe == 0)
			dire = _which(datash->args[0], datash->_environ);
		else
			dire = datash->args[0];
		execve(dire + exe, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &stat, WUNTRACED);
		} while (!WIFEXITED(stat) && !WIFSIGNALED(stat));
	}

	datash->status = stat / 256;
	return (1);
}
