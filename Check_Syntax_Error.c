#include "shell.h"

/**
 * Repeated_Char - Counts the number of occurrences of a character.
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */

int Repeated_Char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (Repeated_Char(input - 1, i + 1));
	return (i);
}

/**
 * Error_Sep_Op - Finds syntax errors related to seperators and operators.
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no errors
 */
int Error_Sep_Op(char *input, int i, char last)
{
	int c;

	c = 0;
	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (Error_Sep_Op(input + 1, i + 1, last));
	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);
	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);
		if (last == '|')
		{
			c = Repeated_Char(input, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);
		if (last == '&')
		{
			c = Repeated_Char(input, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}
	return (Error_Sep_Op(input + 1, i + 1, *input));
}

/**
 * First_Char - Finds the index of the first char
 * @input: input string
 * @i: index
 * Return: 1 if there is an error, 0 in other cases
 */

int First_Char(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;
		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
 * Print_Syntax_Error - Prints a message when a syntax error is found.
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: nothing
 */

void Print_Syntax_Error(data_shell *datash, char *input, int i, int bool)
{
	char *Msg, *Msg2, *Msg3, *Error, *Counter;
	int Length;

	if (input[i] == ';')
	{
		if (bool == 0)
			Msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			Msg = (input[i - 1] == ';' ? ";;" : ";");
	}
	if (input[i] == '|')
		Msg = (input[i + 1] == '|' ? "||" : "|");
	if (input[i] == '&')
		Msg = (input[i + 1] == '&' ? "&&" : "&");
	Msg2 = ": Syntax error: \"";
	Msg3 = "\" unexpected\n";
	Counter = aux_itoa(datash->counter);
	Length = _strlen(datash->av[0]) + _strlen(Counter);
	Length += _strlen(Msg) + _strlen(Msg2) + _strlen(Msg3) + 2;
	Error = malloc(sizeof(char) * (Length + 1));
	if (Error == 0)
	{
		free(Counter);
		return;
	}
	_strcpy(Error, datash->av[0]);
	_strcat(Error, ": ");
	_strcat(Error, Counter);
	_strcat(Error, Msg2);
	_strcat(Error, Msg);
	_strcat(Error, Msg3);
	_strcat(Error, "\0");
	write(STDERR_FILENO, Error, Length);
	free(Error);
	free(Counter);
}

/**
 * Check_Syntax_Error - Intermediate function to find
 * and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error, 0 in other cases
 */

int Check_Syntax_Error(data_shell *datash, char *input)
{
	int Begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = First_Char(input, &Begin);
	if (f_char == -1)
	{
		Print_Syntax_Error(datash, input, Begin, 0);
		return (1);
	}

	i = Error_Sep_Op(input + Begin, 0, *(input + Begin));
	if (i != 0)
	{
		Print_Syntax_Error(datash, input, Begin + i, 1);
		return (1);
	}
	return (0);
}
