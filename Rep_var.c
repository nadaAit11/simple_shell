#include "shell.h"

/**
 * check_env - checks if the typed variable is an env variable
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: nothing
 */

void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, j, lval;
	char **_envi;

	_envi = data->_environ;
	for (row = 0; _envi[row]; row++)
	{
		for (j = 1, chr = 0; _envi[row][chr]; chr++)
		{
			if (_envi[row][chr] == '=')
			{
				lval = _strlen(_envi[row] + chr + 1);
				add_rvar_node(h, j, _envi[row] + chr + 1, lval);
				return;
			}
			if (in[j] == _envi[row][chr])
				j++;
			else
				break;
		}
	}
	for (j = 0; in[j]; j++)
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;

	add_rvar_node(h, j, NULL, 0);
}
/**
 * check_vars - check if the typed variable is $$ or $?
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the shell
 * @data: data structure
 * Return: nothing
 */

int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int i, ls, lpd;

	ls = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node(h, 2, st, ls), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}
	return (i);
}
/**
 * replaced_input - replaces string into variables
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */

char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					new_input[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}
	return (new_input);
}
/**
 * rep_var - calls functions to replace string into vars
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *index;
	char *stat, *new_input;
	int olen, nlen;

	stat = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, stat, datash);

	if (head == NULL)
	{
		free(stat);
		return (input);
	}
	index = head;
	nlen = 0;

	while (index != NULL)
	{
		nlen += (index->len_val - index->len_var);
		index = index->next;
	}
	nlen += olen;
	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(stat);
	free_rvar_list(&head);

	return (new_input);
}
