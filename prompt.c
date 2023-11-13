#include "shell.h"
/**
 * sig_handler - handler cntrl c
 * @num: num argument
 */
void sig_handler(int num)
{
	(void)num;
	write(STDOUT_FILENO, "\n🤭:~$ ", _strlen("\n🤭:~$ "));
}


/**
 * prompt - a shell using c
 * @arc: argument count
 * @arv: argument by user
 * @envp: environment variable argument
 * @interactive: flag argument for mode
 */
void prompt(int arc, char **arv, char **envp, bool interactive)
{
	size_t n = 0;
	ssize_t num_char = 0;
	char *cmd = NULL;
	char *token[MAX_C];
	char *prompt = "😃:~$ ";
	int x;

	while (1)
	{
		if (!interactive && isatty(STDIN_FILENO))
			check_active(arc, arv, envp);
		else
			write(STDOUT_FILENO, prompt, _strlen(prompt));
		signal(SIGINT, sig_handler);
		num_char = getline(&cmd, &n, stdin);
		if (num_char == -1) /*handles the end file case*/
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		if (cmd[num_char - 1] == '\n')
		{
			cmd[num_char - 1] = '\0';
		}
		cmd = white_space(cmd);
		if (_strlen(cmd) == 0)
			continue;
		x = 0;
		token[x] = strtok(cmd, " \n");
		handle_exit(cmd);
		handle_path(token, cmd);
		while (token[x])
		{
			x++;
			token[x] = strtok(NULL, " \n");
		}
		execution(token, arv, envp); /* envir */
	}

	free(cmd);
}
