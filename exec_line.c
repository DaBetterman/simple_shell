#include "shell.h"

/**
 * exec_line - finds builtins and commands
 *
 * @database: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data *database)
{
	int (*builtin)(data *database);

	/*Check if there are no arguments provided*/
	if (database->args[0] == NULL)
		return (1);

	/*Try to find a matching built-in command and get its function pointer*/
	builtin = get_builtin(database->args[0]);

	/*If a matching built-in command is found, execute it*/
	if (builtin != NULL)
		return (builtin(database));

	/*If no built-in command is found, execute an external command*/
	return (cmd_exec(database));
}
