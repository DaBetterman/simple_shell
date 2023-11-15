#include "shell.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	/*Calculate the lengths of the name and value*/
	len_name = _strlen(name);
	len_value = _strlen(value);

	/*Calculate the total length needed for the new environment variable or alias*/
	len = len_name + len_value + 2;

	/*Allocate memory for the new environment variable or alias*/
	new = malloc(sizeof(char) * (len));

	/*Copy the name into the new variable*/
	_strcpy(new, name);

	/*Add the equal sign to separate the name and value*/
	_strcat(new, "=");

	/*Concatenate the value to the new variable*/
	_strcat(new, value);

	/*Add a null terminator to the end of the new variable*/
	_strcat(new, "\0");

	/*Return the new environment variable or alias*/
	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @database: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data *database)
{
	int i;
	char *var_env, *name_env;

	/*Iterate through the array of environment variables to find the one to update*/
	for (i = 0; database->_environ[i]; i++)
	{
		/*Duplicate the environment variable to work with*/
		var_env = _strdup(database->_environ[i]);
		name_env = _strtok(var_env, "=");

		/*Check if the current variable's name matches the one to update*/
		if (_strcmp(name_env, name) == 0)
		{
			/*Update the existing variable and return*/
			free(database->_environ[i]);
			database->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	/*If the variable is not found, allocate memory for the new environment variable*/
	database->_environ = _reallocdp(database->_environ, i, sizeof(char *) * (i + 2));

	/*Add the new environment variable*/
	database->_environ[i] = copy_info(name, value);

	/*Mark the end of the environment variables*/
	database->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @database: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data *database)
{

	/*Check if the required arguments are not provided*/
	if (database->args[1] == NULL || database->args[2] == NULL)
	{
		/*Set an error status if arguments are missing*/
		get_error(database, -1);
		return (1);
	}

	/*Call a function to set or update the environment variable with the specified name and value*/
	set_env(database->args[1], database->args[2], database);

	/*Return 1 to indicate success*/
	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @database: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data *database)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	/*Check if the environment variable name is not provided*/
	if (database->args[1] == NULL)
	{
		get_error(database, -1);
		return (1);
	}
	k = -1;

	/*Iterate through the array of environment*/
	/*variables to find the one to delete*/
	for (i = 0; database->_environ[i]; i++)
	{
		/*Duplicate the environment variable to work with*/
		var_env = _strdup(database->_environ[i]);
		name_env = _strtok(var_env, "=");

		/*Check if the current variable matches the one to delete*/
		if (_strcmp(name_env, database->args[1]) == 0)
		{
			/*Store the index of the variable to delete*/
			k = i;
		}
		/*Free the duplicated variable*/
		free(var_env);
	}
	/*If the variable to delete is not found, set an error and return*/
	if (k == -1)
	{
		get_error(database, -1);
		return (1);
	}

	/*Allocate memory for the new environment variable array*/
	realloc_environ = malloc(sizeof(char *) * (i));

	/*Copy the existing environment variables*/
	/*to the new array, excluding the one to delete*/
	for (i = j = 0; database->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = database->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;

	/*Free the memory of the old environment variable array and update it with the new one*/
	free(database->_environ[k]);
	free(database->_environ);
	database->_environ = realloc_environ;

	/*Return 1 to indicate success*/
	return (1);
}
