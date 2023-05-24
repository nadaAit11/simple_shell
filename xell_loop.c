#include "shell.h"

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *without_comment(char *in)
{
	int j, UP_TO;

	UP_TO = 0;
	for (j = 0; in[j]; j++)
	{
		if (in[j] == '#')
		{
			if (j == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[j - 1] == ' ' || in[j - 1] == '\t' || in[j - 1] == ';')
				UP_TO = j;
		}
	}
	if (UP_TO != 0)
	{
		in = _realloc(in, j, UP_TO + 1);
		in[UP_TO] = '\0';
	}
	return (in);
}
/**
 * shell_loop - loop of shell
 * @datash: data relevant
 *
 * Return: nothing
 */
void shell_loop(data_shell *datash)
{
	int LOOP, i_eof;
	char *inp;

	LOOP = 1;
	while (LOOP == 1)
	{
		write(STDIN_FILENO, "^,- ", 4);
		inp = read_line(&i_eof);
		if (i_eof != -1)
		{
			inp = without_comment(inp);
			if (inp == NULL)
				continue;
			if (Check_Syntax_Error(datash, inp) == 1)
			{
				datash->status = 2;
				free(inp);
				continue;
			}
			inp = rep_var(inp, datash);
			LOOP = split_commands(datash, inp);
			datash->counter += 1;
			free(inp);
		}
		else
		{
			LOOP = 0;
			free(inp);
		}
	}
}
