#include "shell.h"

/**
 * exit_shell - exits the shell
 *
 * @database: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data *database)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	/*Check if there is an argument provided to specify the exit status*/
	if (database->args[1] != NULL)
	{
		/*Convert the exit status argument to an unsigned integer*/
		ustatus = _atoi(database->args[1]);

		/*Check if the argument is a digit and its length*/
		is_digit = _isdigit(database->args[1]);
		str_len = _strlen(database->args[1]);

		/*Check if the exit status is too large to fit in INT_MAX*/
		big_number = ustatus > (unsigned int)INT_MAX;

		/*If any of the above checks fail, set an error status and return*/
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(database, 2);
			database->status = 2;
			return (1);
		}

		/*Set the shell's status to the exit status (limited to 8 bits)*/
		database->status = (ustatus % 256);
	}
	/*Return 0 to indicate success*/
	return (0);
}
