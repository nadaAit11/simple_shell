#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>


#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"


/* points to an array of pointers to strings called the "environment" */
extern char **environ;



/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */

typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;


/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */

typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;


/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */

typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;


/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */

typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;


/**
 * struct builtin_s - builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;


/* Lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);


/* Lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* Str.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);


/* Gen_mem.c */
void _Memcpy(void *newptr, const void *ptr, unsigned int size);
void *_Realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_Reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);


/* Str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* Str3.c */
void rev_string(char *s);


/* Check_Syntax_Error.c */
int Repeated_Char(char *input, int i);
int Error_Sep_Op(char *input, int i, char last);
int First_Char(char *input, int *i);
void Print_Syntax_Error(data_shell *datash, char *input, int i, int bool);
int Check_Syntax_Error(data_shell *datash, char *input);


/* xell_loop.c */
char *without_comment(char *in);
void shell_loop(data_shell *datash);


/* Read_Line.c */
char *read_line(int *i_eof);


/* Split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);


/* Rep_var.c */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *datash);


/* Get_Line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);


/* Exec_Line */
int Exec_Line(data_shell *datash);


/* Cmd_exec.c */
int Is_Cdir(char *path, int *i);
char *_Which(char *cmd, char **_environ);
int Is_Executable(data_shell *datash);
int Check_Error_Cmd(char *dir, data_shell *datash);
int Cmd_Exec(data_shell *datash);


/* Env1.c */
char *_Getenv(const char *name, char **_environ);
int _Env(data_shell *datash);


/* Env2.c */
char *Copy_Info(char *name, char *value);
void Set_Env(char *name, char *value, data_shell *datash);
int _Setenv(data_shell *datash);
int _Unsetenv(data_shell *datash);


/* Cd.c */
void Cd_dot(data_shell *datash);
void Cd_to(data_shell *datash);
void Cd_previous(data_shell *datash);
void Cd_to_home(data_shell *datash);


/* Cd_shell.c */
int Cd_shell(data_shell *datash);


/* get_built_in.c */
int (*get_builtin(char *cmd))(data_shell *datash);


/* exit_xell.c */
int exit_shell(data_shell *datash);


/* STD_lib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);


/* Error1.c */
char *Strcat_Cd(data_shell *, char *, char *, char *);
char *Error_Get_Cd(data_shell *datash);
char *Error_Not_Found(data_shell *datash);
char *Error_Exit_Shell(data_shell *datash);


/* Error2.c */
char *error_get_alias(char **args);
char *Error_Env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *Error_Path_126(data_shell *datash);



/* Get_Error.c */
int get_error(data_shell *datash, int eval);


/* Get_Sigint.c */
void get_sigint(int sig);


/* Help1.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);


/* Help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);


/* Get_Help.c */
int get_help(data_shell *datash);


#endif
