#include "shell.h"

/**
 * free_data - frees data structure
 *
 * @database: data structure
 * Return: no return
 */
void free_data(data *database)
{
	unsigned int i;

/*Loop through the _environ array and free each environment variable*/
	for (i = 0; database->_environ[i]; i++)
	{
		free(database->_environ[i]);
	}

/*Free the memory allocated for the _environ array*/
	free(database->_environ);

/*Free the memory allocated for the process ID*/
	free(database->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @database: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data *database, char **av)
{
	unsigned int i;

/*Store the argument vector in the data structure*/
	database->av = av;

/*Initialize some data structure fields*/
	database->input = NULL;
	database->args = NULL;
	database->status = 0;
	database->counter = 1;

/*Count the number of environment variables*/
	for (i = 0; environ[i]; i++)
	{

	}

/*Allocate memory for the data structure's environment variable array*/
	database->_environ = malloc(sizeof(char *) * (i + 1));

	if (database->_environ == NULL)
	{
		perror("error main.c.53");
	}


/*Copy environment variables into the data structure*/
	for (i = 0; environ[i]; i++)
	{
		database->_environ[i] = _strdup(environ[i]);
	}

/*Set the last element of the environment variable array to NULL*/
	database->_environ[i] = NULL;

/*Store the process ID in the data structure*/
	database->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data database;
	(void) ac;

/*Set up a signal handler for Ctrl+C*/
	signal(SIGINT, get_sigint);

/*Initialize the database structure with command-line arguments*/
	set_data(&database, av);

/*Start the main shell loop*/
	shell_loop(&database);

/*Free any allocated resources*/
	free_data(&database);
/*Check if the status is less than 0*/
/*If so, return 255 which is commonly used for error conditions*/
	if (database.status < 0)
		return (255);

/*Return the status of the program*/
	return (database.status);
}
