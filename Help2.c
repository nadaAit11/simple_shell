#include "shell.h"

/**
 * aux_help - help information for the built-in help
 * Return: void
 */

void aux_help(void)
{
	char *Help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, Help, _strlen(Help));
}

/**
 * aux_help_alias - help information for the builtin alias.
 * Return: nothing
 */

void aux_help_alias(void)
{
	char *Help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, Help, _strlen(Help));
}

/**
 * aux_help_cd - help information for the builtin alias
 * Return: nothing
 */

void aux_help_cd(void)
{
	char *Help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, Help, _strlen(Help));
	Help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, Help, _strlen(Help));
}
