#include "shell.h"

/**
 * read_line - reads the input string
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufSize = 0;

	*i_eof = getline(&input, &bufSize, stdin);

	return (input);
}
