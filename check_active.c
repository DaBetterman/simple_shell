#include "shell.h"

/**
* execute_command - Function to execute a command.
* @full_path: The full path to the command to be executed.
* @new_arv: Array of strings representing the arguments for the command.
* @new_envp: Array of strings representing the
*				environment variables for the command.
* @isInteractive: Flag indicating whether the
*					execution is in interactive mode (1) or not (0).
* @inputBuffer: Buffer containing the input data if not in interactive mode.
* @arv: Array of strings representing the command-line arguments.
* @arc: Number of command-line arguments.
* @command: The command to be executed.
*
* Return: This function does not return.
*/


void execute_command(char *full_path, char **new_arv, char **new_envp,
int isInteractive, char *inputBuffer, char **arv, int arc, char *command)
{
	FILE *fp;

	if (isInteractive)
	{
		/* Execute the command in interactive mode */
		execve(full_path, new_arv, new_envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		fp = fopen(full_path, "r");

		if (fp == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		fprintf(fp, "%s", inputBuffer);
		fclose(fp);
		fprintf(stderr, "%s: %d: %s: not found\n", arv[0], arc, command);
		exit(EXIT_SUCCESS);
	}
}

/**
* search_and_execute - Search for the command
*						in PATH directories and execute it.
* @token: Tokenized PATH directories.
* @command: The command to be searched and executed.
* @new_arv: Array of strings representing the arguments for the command.
* @isInteractive: Indicating if the execution is interactive (1) or not (0).
* @inputBuffer: Buffer containing the input data if not in interactive mode.
* @arv: Array of strings representing the command-line arguments.
* @arc: Number of command-line arguments.
*
* Return: Void
*/
void search_and_execute(char *token, char *command, char **new_arv,
int isInteractive, char *inputBuffer, char **arv, int arc)
{
	char full_path[1024];

	char *new_envp[] = {NULL};

	while (token != NULL)
	{
		/* Construct the full path to the command */
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			/* Execute the command if found */
			execute_command(full_path, new_arv, new_envp,
			isInteractive, inputBuffer, arv, arc, command);
		}
		token = strtok(NULL, ":");
	}
}

/**
 * check_active - Check if a command is active in the PATH directories.
 * @arc: Number of command-line arguments.
 * @arv: Array of strings representing the command-line arguments.
 * @envp: Array of strings representing the environment variables.
 *
 * Return: Void
 */
void check_active(int arc, char **arv, char **envp)
{
	int isInteractive = isatty(0);

	char inputBuffer[1024];
	char *command = arv[1];
	char *commandOne = arv[2];

	char *path = _getenv("PATH", envp);

	char *token = strtok(path, ":");

	char *new_arv[] = {NULL, NULL, NULL};

	new_arv[0] = command;
	new_arv[1] = commandOne;

	if (arc > 5)
	{
		/* Display usage information for incorrect command line arguments */
		fprintf(stderr, "Usage: %s <command> <commandOne>\n", arv[0]);
		exit(EXIT_FAILURE);
	}
	if (isInteractive != 1)
	{
		/* Read input from the pipeline if not in interactive mode */
		if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL)
		{
			fprintf(stderr, "Error reading input from the pipeline\n");
			exit(EXIT_FAILURE);
		}
		inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
	}
	/* Search and execute the command in PATH directories */
	search_and_execute(token, command, new_arv,
	isInteractive, inputBuffer, arv, arc);
	/* Display error message if the command is not found */
	if (isInteractive)
		fprintf(stderr, "'%s' not found in any PATH directory.\n", commandOne);
	else
		fprintf(stderr, "%s: %d: %s: not found\n", arv[0], arc, arv[1]);
	exit(EXIT_FAILURE);
}
