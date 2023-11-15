#include "shell.h"


/**
 * is_cdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{

	/*Check if the current character is a colon (":")*/
	if (path[*i] == ':')
		return (1);

	/*Iterate through characters until a colon or the end of the string is found*/
	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	/*If a colon is found, move the index to the next character*/
	if (path[*i])
		*i += 1;

	/*Return 0, indicating that the current directory is not represented by ":""*/
	return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	/*Get the PATH environment variable*/
	path = _getenv("PATH", _environ);
	if (path)
	{
		/*Duplicate the PATH to avoid modifying the original*/
		ptr_path = _strdup(path);

		/*Calculate the length of the command name*/
		len_cmd = _strlen(cmd);

		/*Tokenize the PATH variable using colons as separators*/
		token_path = _strtok(ptr_path, ":");
		i = 0;

		/*Iterate through the directories in the PATH*/
		while (token_path != NULL)
		{
			/*Check if the current directory is ".", indicating the current directory*/
			if (is_cdir(path, &i))

				/*Check if the command is executable in the current directory*/
				if (stat(cmd, &st) == 0)
					return (cmd);

			/*Calculate the length of the current directory*/
			len_dir = _strlen(token_path);

			/*Allocate memory for the full path to the command*/
			dir = malloc(len_dir + len_cmd + 2);

			/*Copy the directory path, followed by a slash, the command name, and null terminator*/
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");

			/*Check if the command is executable in the current directory*/
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}

			/*Free the memory allocated for the directory path*/
			free(dir);

			/*Move to the next directory in the PATH*/
			token_path = _strtok(NULL, ":");
		}

		/*Free the duplicated PATH*/
		free(ptr_path);

		/*Check if the command is executable in the current directory (if PATH is empty)*/
		if (stat(cmd, &st) == 0)
			return (cmd);

		/*Return NULL if the command is not found*/
		return (NULL);
	}

	/*Check if the command has an absolute path (starts with '/')*/
	if (cmd[0] == '/')

		/*Check if the command is executable at the specified absolute path*/
		if (stat(cmd, &st) == 0)
			return (cmd);

	/*Return NULL if the command is not found*/
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @database: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable(data *database)
{
	struct stat st;/*A structure to store information about the file*/
	int i;
	char *input;

	/*Get the command from the data structure*/
	input = database->args[0];

	/*Iterate through the characters of the input command*/
	for (i = 0; input[i]; i++)
	{

		/*Check for dot (.) character*/
		if (input[i] == '.')
		{
			/*Double dot ".." is not allowed*/
			if (input[i + 1] == '.')
				return (0);

			/*Skip "./" at the beginning*/
			if (input[i + 1] == '/')
				continue;
			else

			/*Exit loop if there's a dot not followed by slash*/
				break;
		}
		else if (input[i] == '/' && i != 0)
		{

			/*Skip "../" or ".." after a slash*/
			if (input[i + 1] == '.')
				continue;
			/*Move to the character after the slash*/
			i++;

			/*Exit loop if there's a valid path separator*/
			break;
		}
		else
			break;
	}

	/* Check if the provided command contains valid characters */
	if (i == 0)
		return (0);

	/* Check if the file or command is accessible and get information about it */
	if (stat(input + i, &st) == 0)
	{

		/*Return the position of the first character in the executable*/
		return (i);
	}

	/*Set an error status for "command not found"*/
	get_error(database, 127);

	/*Return -1 to indicate that it's not an executable*/
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @database: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *dir, data *database)
{

	/* Check if the directory is NULL, indicating the command was not found in the system */
	if (dir == NULL)
	{
		/*Set an error status for "command not found"*/
		get_error(database, 127);
		return (1);
	}

	/* Check if the provided command is not the same as the located directory */
	if (_strcmp(database->args[0], dir) != 0)
	{

		/* Check if the user has execute (X_OK) permissions for the located directory */
		if (access(dir, X_OK) == -1)
		{

			/*Set an error status for "permission denied"*/
			get_error(database, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{

		 /* Check if the user has execute (X_OK) permissions for the provided command */
		if (access(database->args[0], X_OK) == -1)
		{
			/*Set an error status for "permission denied"*/
			get_error(database, 126);
			return (1);
		}
	}

	/*Return 0 to indicate no errors*/
	return (0);
}

/**
 * cmd_exec - executes command lines
 *
 * @database: data relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec(data *database)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;

	/*This line is included to avoid unused variable warnings*/
	(void) wpd;

	/* Check if the command is executable */
	exec = is_executable(database);

	/* If the command is not executable, try to find its location */
	if (exec == -1)
		return (1);
	if (exec == 0)
	{

		/* If not found in the current directory, search for the command in the system's PATH */
		dir = _which(database->args[0], database->_environ);

		/*Check if there was an error while searching for the command */
		if (check_error_cmd(dir, database) == 1)
			return (1);
	}

	/* Create a child process */
	pd = fork();

	/* Child process */
	if (pd == 0)
	{

		/* Determine the location of the command */
		if (exec == 0)
			dir = _which(database->args[0], database->_environ);
		else
			dir = database->args[0];

		/* Execute the command using the specified arguments and environment variables */
		execve(dir + exec, database->args, database->_environ);
	}

	/* Error occurred while forking */
	else if (pd < 0)
	{
		/* Print an error message */
		perror(database->av[0]);
		return (1);
	}
	/* Parent process */
	else
	{

		/* Wait for the child process to finish */
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	/* Set the shell's status to the exit status of the executed command */
	database->status = state / 256;

	/* Return 1 to indicate success */
	return (1);
}
