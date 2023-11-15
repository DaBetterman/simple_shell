#include "shell.h"

/**
 * swap_char - Swaps '|' and '&' for non-printed characters and vice versa.
 *
 * @input: Input string to process.
 * @bool: Type of swap (0 for non-printed to special characters, 1 for special characters to non-printed).
 * Return: Swapped string.
 */
char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		/* Swap '|' for non-printed character 16 and handle double '|' */
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			/* Swap '&' for non-printed character 12 and handle double '&' */
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		/* Swap non-printed character 16 back to '|' and non-printed character 12 back to '&' */
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}


/**
 * add_nodes - Adds separators and command lines to the respective lists.
 *
 * @head_s: Pointer to the head of the separator list.
 * @head_l: Pointer to the head of the command lines list.
 * @input: Input string to process.
 * Return: No return value.
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	/* Swap special characters '|' and '&' for non-printed chars */
	input = swap_char(input, 0);

	/* Iterate through the input string to find separators and add them to the separator list */
	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	/* Tokenize the input string using separators and add the resulting command lines to the list */
	line = _strtok(input, ";|&");
	do {
		/* Swap special characters back to their original form */
		line = swap_char(line, 1);

		/* Add the command line to the command lines list */
		add_line_node_end(head_l, line);

		/* Get the next command line using strtok */
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}


/**
 * go_next - Moves to the next command line and separator in the stored lists.
 *
 * @list_s: Pointer to the separator list.
 * @list_l: Pointer to the command line list.
 * @database: Data structure containing shell information.
 * Return: No return value.
 */
void go_next(sep_list **list_s, line_list **list_l, data *database)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	/* Initialize the loop control variable */
	loop_sep = 1;

	/* Get references to the separator and command line lists */
	ls_s = *list_s;
	ls_l = *list_l;

	/* Iterate through the separator list to find the next command line */
	while (ls_s != NULL && loop_sep)
	{
		if (database->status == 0)
		{
			/* If the status is 0 (indicating success), handle '&' and ';' separators */
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			/* If the status is not 0 (indicating failure), handle '|' and '&' separators */
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}

		/* Check if there's another separator when loop_sep is false */
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	/* Update the pointers to the separator and command line lists */
	*list_s = ls_s;
	*list_l = ls_l;
}


/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @database: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data *database, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	/*Initialize a linked list to store separators*/
	head_s = NULL;

	/*Initialize a linked list to store lines*/
	head_l = NULL;

	/*Parse the input and add nodes to the linked lists*/
	add_nodes(&head_s, &head_l, input);

	/*Initialize the separator list*/
	list_s = head_s;

	/*Initialize the line list*/
	list_l = head_l;

	while (list_l != NULL)
	{
		/*Set the input to the current line*/
		database->input = list_l->line;

		/*Split the line into arguments*/
		database->args = split_line(database->input);

		/*Execute the line and get the result*/
		loop = exec_line(database);

		/*Free the arguments*/
		free(database->args);

		/*If loop is 0 (indicating an exit command), break out of the loop*/
		if (loop == 0)
			break;

		/*Move to the next separator and line*/
		go_next(&list_s, &list_l, database);

		/*Move to the next line*/
		if (list_l != NULL)
			list_l = list_l->next;
	}

	/*Free the separator list*/
	free_sep_list(&head_s);

	/*Free the line list*/
	free_line_list(&head_l);

	/**If the loop is 0, return 0 to indicate exit
	 * else return 1 to continue*/
	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - Tokenizes the input string into an array of tokens.
 *
 * @input: The input string to tokenize.
 * Return: An array of tokens.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	/* Initialize the buffer size */
	bsize = TOK_BUFSIZE;

	/* Allocate memory for the tokens array */
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		/* Error handling for memory allocation */
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	/* Tokenize the input string using the specified delimiters */
	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	/* Iterate through the input and tokenize it */
	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			/* Increase the buffer size if necessary */
			bsize += TOK_BUFSIZE;

			/* Reallocate memory for the tokens array */
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				/* Error handling for memory allocation */
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}

		/* Continue tokenizing the input */
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return tokens;
}
