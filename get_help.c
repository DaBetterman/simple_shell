#include "shell.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @database: data structure (args and input)
 * Return: Return 0
*/
int get_help(data *database)
{

	/*Check if there is no specific command provided*/
	if (database->args[1] == 0)

		/*Call a general help function*/
		aux_help_general();

	/*Check for specific commands and call their respective help functions*/
	else if (_strcmp(database->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(database->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(database->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(database->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(database->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(database->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(database->args[1], "alias") == 0)
		aux_help_alias();
	else
		/*If the command is not recognized,*/
		/*write an error message to the standard error output*/
		write(STDERR_FILENO, database->args[0],
		      _strlen(database->args[0]));
	/*Set the status to 0 (possibly indicating success)*/
	database->status = 0;

	/*Return 1 (possibly indicating that the function executed)*/
	return (1);
}
