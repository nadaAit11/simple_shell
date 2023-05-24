#include "shell.h"

/**
 * Cd_shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */

int Cd_shell(data_shell *datash)
{
	char *dire;
	int isHome, isHome2, isDdash;

	dire = datash->args[1];

	if (dire != NULL)
	{
		isHome = _strcmp("$HOME", dire);
		isHome2 = _strcmp("~", dire);
		isDdash = _strcmp("--", dire);
	}
	if (dire == NULL || !isHome || !isHome2 || !isDdash)
	{
		Cd_to_home(datash);
		return (1);
	}
	if (_strcmp("-", dire) == 0)
	{
		Cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dire) == 0 || _strcmp("..", dire) == 0)
	{
		Cd_dot(datash);
		return (1);
	}

	Cd_to(datash);

	return (1);
}
