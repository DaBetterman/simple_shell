#include "shell.h"
/**
 * handle_path - handle the path function
 * @token: token argument
 * @cmd: command set by the user
 * Return: command for exec
 */
char *handle_path(char **token, char *cmd)
{
	char *path;

	path = malloc(_strlen("/bin/") + _strlen(cmd) + 1);
	if (!path)
	{
		return (NULL);
	}
	_strcpy(path, "/bin/");

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		token[0] = _strcat(path, cmd);
		return (token[0]);
	}
	free(path);
	return (cmd);
}
