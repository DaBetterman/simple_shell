#include "shell.h"

/**
 * get_builtin - builtin that pass the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data *)
{
	/*Define an array of structs containing built-in*/
	/*command names and their corresponding functions*/
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	}; /*This marks the end of the array*/

	int i;

	/*Iterate through the array to find the matching command name*/
	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}
	/*Return the function pointer associated with the matched built-in command*/
	return (builtin[i].f);
}
