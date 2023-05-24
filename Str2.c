#include "shell.h"

/**
 * _strdup - duplicates a str in the heap memory
 * @s: type char ppointer str
 * Return: duplicated str
 */

char *_strdup(const char *s)
{
	char *new;
	size_t length;

	length = _strlen(s);
	new = malloc(sizeof(char) * (length + 1));
	if (new == NULL)
		return (NULL);
	_Memcpy(new, s, length + 1);
	return (new);
}

/**
 * _strlen - returns the length of a string
 * @s: type char pointer
 * Return: always 0
 */
int _strlen(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * cmp_chars - compare chars of strings
 * @str : input string
 * @delim: delimiter
 * Return: 1 if are equals, 0 if not
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter
 * @str: input string
 * @delim: delimiter
 * Return: string splited
 */

char *_strtok(char str[], const char *delim)
{
	static char *splitted, *string_end;
	char *string_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str;
		i = _strlen(str);
		string_end = &str[i];
	}
	string_start = splitted;
	if (string_start == string_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != string_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == string_start)
					string_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (string_start);
}

/**
 * _isdigit - defines if a string is a number
 * @s: input string
 * Return: 1 if it is a number, 0 in other case
 */

int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
