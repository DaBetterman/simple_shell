#include "shell.h"

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *without_comment(char *in)
{
	int i, up_to;

/**Initialize a variable to keep track of the
 * position up to which comments should be removed*/
	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		/*Check if a comment symbol '#' is found in the input*/
		if (in[i] == '#')
		{
			/*If '#' is the first character, we discard the whole input*/
			if (i == 0)
			{
				/**Free the memory allocated for the input
				 * and return NULL to indicate an empty input*/
				free(in);
				return (NULL);
			}

				/*Check if the character before '#' is a space, tab, or semicolon*/
			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')

			/*Set 'up_to' to the position just before the comment symbol*/
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		/*Resize the input to remove the comment*/
		in = _realloc(in, i, up_to + 1);

		/*Terminate the string at the position 'up_to'*/
		in[up_to] = '\0';
	}

/*Return the modified input without comments*/
	return (in);
}

/**
 * shell_loop - Loop of shell
 * @database: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(data *database)
{
	int loop, i_eof;
	char *input;
	

/*Set the loop variable to 1, indicating that the loop should continue*/
	loop = 1;

/*Continue looping while the loop variable is 1*/
	while (loop == 1)
	{
		/*Display a prompt "😃:~$ " to the user*/
		write(STDIN_FILENO, "😃:~$ ", 8);

		/*Read a line of user input*/
		input = read_line(&i_eof);

		/*Check if the input didn't encounter an end-of-file condition*/
		if (i_eof == -1)
		{
			/*Set the loop variable to 0 to exit the loop*/
			loop = 0;

			/*Free the input*/
			free(input);
		}
		else
		{
			/*Remove comments from the input*/
			input = without_comment(input);

			/*If input becomes empty after removing comments, continue the loop*/
			if (input == NULL)
				continue;
			/*Check for syntax errors in the input*/
			if (check_syntax_error(database, input) == 1)
			{
				/*Set the status to 2 if there's a syntax error*/
				database->status = 2;

				/*Free the input & continue the loop*/
				free(input);
				continue;
			}

			/*Replace variables in the input*/
			input = rep_var(input, database);

			/*Split and execute commands, updating the loop variable*/
			loop = split_commands(database, input);

			/*Increase the command counter*/
			database->counter += 1;

			/*Free the input & continue the loop*/
			free(input);
		}
	}
}
