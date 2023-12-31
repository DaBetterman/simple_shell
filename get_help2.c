#include "shell.h"

/**
 * aux_help - Help information for the built-in help command.
 * Return: No return.
 */

void aux_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	/*Write the help information to the standard output*/
	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * aux_help_alias - Help information for the built-in alias command.
 * Return: No return.
 */
void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	/*Write the help information to the standard output*/
	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * aux_help_cd - Help information for the built-in cd command.
 * Return: No return.
 */
void aux_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	/*Write the help information to the standard output*/
	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
