#include "shell.h"

/**
 * swap_char - swaps | and & for non-printed chars
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_char(char *input, int bool)
{
	int l;

	if (bool == 0)
	{
		for (l = 0; input[l]; l++)
		{
			if (input[l] == '|')
			{
				if (input[l + 1] != '|')
					input[l] = 16;
				else
					l++;
			}
			if (input[l] == '&')
			{
				if (input[l + 1] != '&')
					input[l] = 12;
				else
					l++;
			}
		}
	}
	else
	{
		for (l = 0; input[l]; l++)
		{
			input[l] = (input[l] == 16 ? '|' : input[l]);
			input[l] = (input[l] == 12 ? '&' : input[l]);
		}
	}
	return (input);
}
/**
 * add_nodes - add separators and command lines in the lists
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: void
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *ln;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);
		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}
	ln = _strtok(input, ";|&");
	do {
		ln = swap_char(ln, 1);
		add_line_node_end(head_l, ln);
		ln = _strtok(NULL, ";|&");
	} while (ln != NULL);
}
/**
 * go_next - go to the next command line stored
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: void
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_separ;
	sep_list *ls_s;
	line_list *ls_l;

	loop_separ = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_separ)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_separ = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_separ = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_separ)
			ls_s = ls_s->next;
	}
	*list_s = ls_s;
	*list_l = ls_l;
}
/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_shell *datash, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int Loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = Exec_Line(datash);
		free(datash->args);

		if (Loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}
	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (Loop == 0)
		return (0);
	return (1);
}
/**
 * split_line - tokenizes the input string
 * @input: input string
 * Return: string splitted
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **Tokens;
	char *Token;

	bsize = TOK_BUFSIZE;
	Tokens = malloc(sizeof(char *) * (bsize));
	if (Tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	Token = _strtok(input, TOK_DELIM);
	Tokens[0] = Token;

	for (i = 1; Token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			Tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (Tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		Token = _strtok(NULL, TOK_DELIM);
		Tokens[i] = Token;
	}
	return (Tokens);
}
