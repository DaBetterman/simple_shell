#include "shell.h"
/**
 * execution - a function that run command
 * @token: token argument
 * @arv: arv argument
 * @envp: envp argument
 */
void execution(char **token, char **arv, char **envp)
{
	pid_t mychild;
	int status;

	mychild = fork();

	if (mychild == -1)
	{
		perror("Process Error");
		exit(EXIT_FAILURE);
	}

	if (mychild == 0)
	{

		if (execve(token[0], token, envp) == (-1))
		{
			write(STDOUT_FILENO, arv[0], _strlen(arv[0]));
			write(STDOUT_FILENO, ": No such file or directory",
			_strlen(": No such file or directory"));
			write(STDOUT_FILENO, "\n", 1);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}
