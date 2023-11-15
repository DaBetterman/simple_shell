#include "shell.h"

/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
	/*Check if the line pointer is initially NULL*/
	if (*lineptr == NULL)
	{
		/*If the buffer size is greater than BUFSIZE,*/
		/*update the size of the line buffer*/
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;

		/*Assign the line pointer to the buffer*/
		*lineptr = buffer;
	}
	/*If the line pointer is not NULL,*/
	/*but the buffer size is greater than the current line size*/
	else if (*n < j)
	{
		/*Update the size of the line buffer*/
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;

		/*Assign the line pointer to the buffer*/
		*lineptr = buffer;
	}
	/*If the line pointer is*/
	/*not NULL and the buffer size is not greater than the line size*/
	else
	{
		/*Copy the contents of the buffer into the line*/
		_strcpy(*lineptr, buffer);

		/*Free the memory used by the buffer*/
		free(buffer);
	}
}


/**
 * get_line - Read input from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	/*If this function is called again*/
	/*before reading the previous input, return an error*/
	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	/*Allocate memory for a buffer to read the input*/
	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);

	/*Read characters from the input stream until a*/
	/*newline character is encountered*/
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);

		/*Check for read errors or if the input is empty*/
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}

		/*If the input is empty, and there was no error, exit the loop*/
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}

		/*If the buffer size is exceeded,*/
		/*reallocate memory to accommodate more characters*/
		if (input >= BUFSIZE)
		{
			buffer = _realloc(buffer, input, input + 1);
		}

		/*Store the character in the buffer and increment the input counter*/
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);

	/*Store the number of bytes read and reset the input counter if necessary*/
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
