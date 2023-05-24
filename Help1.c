#include "shell.h"

/**
 * aux_help_env - help information for the builtin environ.
 * Return: void
 */

void aux_help_env(void)
{
	char *Help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, Help, _strlen(Help));
}

/**
 * aux_help_setenv - help information for the builtin setenv.
 * Return: nothing
 */

void aux_help_setenv(void)
{
	char *Help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "int replace)\n\t";
	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, Help, _strlen(Help));
}

/**
 * aux_help_unsetenv - help information for the builtin unsetenv.
 * Return: nothing
 */

void aux_help_unsetenv(void)
{
	char *Help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, Help, _strlen(Help));
}

/**
 * aux_help_general - entry point for help information for the help builtin.
 * Return: void
 */

void aux_help_general(void)
{
	char *Help = "^,- bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, Help, _strlen(Help));
}

/**
 * aux_help_exit - help information for the builtin exit.
 * Return: void
 */

void aux_help_exit(void)
{
	char *Help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "Exits the shell with a status of N. If N if commited, the exit";
	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "status is that of the last command executed\n";
	write(STDOUT_FILENO, Help, _strlen(Help));
}
