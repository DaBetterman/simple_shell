#include "shell.h"

/**
 * read_line - reads the input string.
 *
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t size = 0;

	/*Read a line of input from the user and store the result in i_eof*/
	*i_eof = getline(&input, &size, stdin);

	return (input);
}
