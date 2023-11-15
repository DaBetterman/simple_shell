#include "shell.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @database: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(data *database, int eval)
{
	char *error;

	/*Check the error code using a switch statement*/
	switch (eval)
	{
	case -1:
		/*Call a function to generate an error*/
		/*message for environment-related errors*/
		error = error_env(database);
		break;
	case 126:
		/*Call a function to generate an error*/
		/*message for a specific path-related error*/
		error = error_path_126(database);
		break;
	case 127:
		/*Call a function to generate an error message when a command is not found*/
		error = error_not_found(database);
		break;
	case 2:

		/*Check if the error is related to "exit" or "cd" commands*/
		if (_strcmp("exit", database->args[0]) == 0)

			/*Get the error message for the "exit" command*/
			error = error_exit_shell(database);
		else if (_strcmp("cd", database->args[0]) == 0)

			/*Get the error message for the "cd" command*/
			error = error_get_cd(database);
		break;
	}

	/*If an error message is available, print it to*/
	/*the standard error output and free the allocated memory*/
	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	/*Update the status in the data structure with the error value and return it*/
	database->status = eval;
	return (eval);
}
