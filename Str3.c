#include "shell.h"

/**
 * rev_string - reverses a string
 * @s: input string
 * Return: nothing
 */
void rev_string(char *s)
{
	int c = 0, k, l;
	char *str, temp;

	while (c >= 0)
	{
		if (s[c] == '\0')
			break;
		c++;
	}
	str = s;

	for (k = 0; k < (c - 1); k++)
	{
		for (l = k + 1; l > 0; l--)
		{
			temp = *(str + l);
			*(str + l) = *(str + (l - 1));
			*(str + (l - 1)) = temp;
		}
	}
}
