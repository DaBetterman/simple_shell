#include "shell.h"

/**
 * error_env - Error message for env in get_env.
 * @database: Data relevant (counter, arguments)
 * Return: Error message.
 */
char *error_env(data *database)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;


	/*Convert the counter to a string*/
	ver_str = aux_itoa(database->counter);

	/*Define the error message*/
	msg = ": Unable to add/remove from environment\n";

	/*Calculate the length of the error message*/
	length = _strlen(database->av[0]) + _strlen(ver_str);
	length += _strlen(database->args[0]) + _strlen(msg) + 4;

	/*Allocate memory for the error message*/
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	/*Construct the error message*/
	_strcpy(error, database->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, database->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");

	/*Free the memory used for the counter string*/
	free(ver_str);

	return (error);
}


/**
 * error_path_126 - Error message for path and permission denied.
 * @database: Data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(data *database)
{
	int length;
	char *ver_str;
	char *error;

	/*Convert the counter to a string*/
	ver_str = aux_itoa(database->counter);

	/*Calculate the length of the error message*/
	length = _strlen(database->av[0]) + _strlen(ver_str);
	length += _strlen(database->args[0]) + 24;

	/*Allocate memory for the error message*/
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	/*Construct the error message*/
	_strcpy(error, database->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, database->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");

	/*Free the memory used for the counter string*/
	free(ver_str);
	return (error);
}
