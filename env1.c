#include "shell.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	/*Iterate through the characters of the environment variable name*/
	for (i = 0; nenv[i] != '='; i++)
	{
		/*Compare each character with the corresponding character in the name*/
		if (nenv[i] != name[i])
		{
			/*Return 0 if a mismatch is found*/
			return (0);
		}
	}

	/*If the loop completes without returning 0, it means the names*/
	/*match & then returns a value other than 0 to indicate a match*/
	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @database: data relevant.
 * Return: 1 on success.
 */
int _env(data *database)
{
	int i, j;

	/*Iterate through the array of environment variables*/
	for (i = 0; database->_environ[i]; i++)
	{
		/*Calculate the length of the current environment variable*/
		for (j = 0; database->_environ[i][j]; j++)
		{

		}

		/*Write the environment variable to the standard output*/
		write(STDOUT_FILENO, database->_environ[i], j);

		/*Write a newline character to separate variables*/
		write(STDOUT_FILENO, "\n", 1);
	}

	/*Set the shell's status to 0 to indicate success*/
	database->status = 0;

	/*Return 1 to indicate success*/
	return (1);
}
