#include "shell.h"
/**
 * white_space - remove leading spaces
 * @cmd: command
 * Return: trimmed command
 */
char *white_space(char *cmd)
{
	char *temp;
	int i = 0;
	int len;

	while (cmd[i] == ' ')
		i++;
	len = _strlen(cmd) - i + 1;
	temp = malloc(len + 1);
	if (!temp)
	{
		perror("Allocation Failed\n");
		return (NULL);
	}
	_strncpy(temp, &cmd[i], len);
	temp[len] = '\0';
	_strcpy(cmd, temp);
	free(temp);
	return (cmd);
}
