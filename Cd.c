#include "shell.h"

/**
 * Cd_dot - changes to the parent directory
 *
 * @datash: data relevant (environ)
 * Return: void
 */
void Cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dire, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	dire = datash->args[1];
	if (_strcmp(".", dire) == 0)
	{
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * Cd_to - changes to a directory given by the user
 * @datash: data relevant (directories)
 * Return: void
 */

void Cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dire, *cp_pwd, *cp_dire;

	getcwd(pwd, sizeof(pwd));

	dire = datash->args[1];
	if (chdir(dire) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dire = _strdup(dire);
	set_env("PWD", cp_dire, datash);

	free(cp_pwd);
	free(cp_dire);

	datash->status = 0;

	chdir(dire);
}

/**
 * Cd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: void
 */

void Cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_Pwd, *p_Oldpwd, *cp_Pwd, *cp_Oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_Pwd = _strdup(pwd);

	p_Oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_Oldpwd == NULL)
		cp_Oldpwd = cp_Pwd;
	else
		cp_Oldpwd = _strdup(p_Oldpwd);

	set_env("OLDPWD", cp_Pwd, datash);

	if (chdir(cp_Oldpwd) == -1)
		set_env("PWD", cp_Pwd, datash);
	else
		set_env("PWD", cp_Oldpwd, datash);

	p_Pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_Pwd, _strlen(p_Pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_Pwd);
	if (p_Oldpwd)
		free(cp_Oldpwd);

	datash->status = 0;

	chdir(p_Pwd);
}

/**
 * Cd_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: void
 */

void Cd_to_home(data_shell *datash)
{
	char *p_Pwd, *Home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_Pwd = _strdup(pwd);

	Home = _getenv("HOME", datash->_environ);

	if (Home == NULL)
	{
		set_env("OLDPWD", p_Pwd, datash);
		free(p_Pwd);
		return;
	}

	if (chdir(Home) == -1)
	{
		get_error(datash, 2);
		free(p_Pwd);
		return;
	}

	set_env("OLDPWD", p_Pwd, datash);
	set_env("PWD", Home, datash);
	free(p_Pwd);
	datash->status = 0;
}
