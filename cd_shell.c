#include "shell.h"

/**
 * cd_shell - changes current directory
 *
 * @database: data relevant
 * Return: 1 on success
 */
int cd_shell(data *database)
{
	char *dir;
	int ishome, ishome2, isddash;

	/*Get the directory argument from user input*/
	dir = database->args[1];

	if (dir != NULL)
	{

		/*Check if the input is "$HOME"*/
		ishome = _strcmp("$HOME", dir);

		/*Check if the input is "~"*/
		ishome2 = _strcmp("~", dir);

		/*Check if the input is "--"*/
		isddash = _strcmp("--", dir);
	}

	/*If the input is empty or matches "$HOME", "~", or "--", change to the home directory*/
	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		/*Change to the home directory*/
		cd_to_home(database);

		/*Return 1 to indicate success*/
		return (1);
	}

	/*If the input is "-", change to the previous directory*/
	if (_strcmp("-", dir) == 0)
	{
		/*Change to the previous directory*/
		cd_previous(database);

		/*Return 1 to indicate success*/
		return (1);
	}

	/*If the input is "." or "..", change to the parent directory or stay in the same directory*/
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		/*Change to the parent directory or stay in the same directory*/
		cd_dot(database);

		/*Return 1 to indicate success*/
		return (1);
	}

	/*Change to the specified directory*/
	cd_to(database);

	/*Return 1 to indicate success*/
	return (1);
}
