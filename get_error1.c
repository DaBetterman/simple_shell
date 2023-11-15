#include "shell.h"

/**
 * strcat_cd - Concatenates parts of an error message for the cd command.
 * @database: Data relevant (directory)
 * @msg: Message to print
 * @error: Output message
 * @ver_str: Counter lines
 * Return: Error message
 */
char *strcat_cd(data *database, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	/*Copy the program name, counter, and part*/
	/*of the error message to the error string*/
	_strcpy(error, database->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, database->args[0]);
	_strcat(error, msg);
	if (database->args[1][0] == '-')
	{
		/*If the argument starts with '-', it's considered an illegal flag*/
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = database->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		/*Otherwise, concatenate the argument as part of the error message*/
		_strcat(error, database->args[1]);
	}

	/*Finalize the error message with newline and null terminator*/
	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}


/**
 * error_get_cd - Error message for the cd command in get_cd.
 * @database: Data relevant (directory)
 * Return: Error message.
 */
char *error_get_cd(data *database)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	/*Convert the counter to a string*/
	ver_str = aux_itoa(database->counter);
	if (database->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(database->args[1]);
	}

	/*Calculate the length of the error message*/
	length = _strlen(database->av[0]) + _strlen(database->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;

	/*Allocate memory for the error message*/
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	/*Construct the error message using strcat_cd function*/
	error = strcat_cd(database, msg, error, ver_str);

	/*Free the memory used for the counter string*/
	free(ver_str);

	return (error);
}


/**
 * error_not_found - Generic error message for command not found.
 * @database: Data relevant (counter, arguments)
 * Return: Error message.
 */
char *error_not_found(data *database)
{
	int length;
	char *error;
	char *ver_str;

	/*Convert the counter to a string*/
	ver_str = aux_itoa(database->counter);

	/*Calculate the length of the error message*/
	length = _strlen(database->av[0]) + _strlen(ver_str);
	length += _strlen(database->args[0]) + 16;

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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");

	/*Free the memory used for the counter string*/
	free(ver_str);
	return (error);
}


/**
 * error_exit_shell - generic error message for exit in get_exit
 * @database: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(data *database)
{
	int length;
	char *error;
	char *ver_str;

	/*Convert the counter to a string*/
	ver_str = aux_itoa(database->counter);

	/*Calculate the length of the error message*/
	length = _strlen(database->av[0]) + _strlen(ver_str);
	length += _strlen(database->args[0]) + _strlen(database->args[1]) + 23;

	/*Allocate memory for the error message*/
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	/*Construct the error message*/
	_strcpy(error, database->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, database->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, database->args[1]);
	_strcat(error, "\n\0");

	/*Free the memory used for the counter string*/
	free(ver_str);

	return (error);
}
