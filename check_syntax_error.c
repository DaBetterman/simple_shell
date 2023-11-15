#include "shell.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int repeated_char(char *input, int i)
{

	/*Check if the previous character is the same as the current character*/
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	/*If the previous character is different, return the count of repetitions*/
	return (i);
}

/**
 * error_sep_op - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;

	/*If the input string is empty, there are no errors, so return 0*/
	if (*input == '\0')
		return (0);

	/*Skip spaces and tabs and continue checking for errors*/
	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	/*Check for specific cases of syntax errors related to separators (;, |, &)*/
	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{

			/*Check for repeated '|' characters, and return an error if there are more than one*/
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{

			/*Check for repeated '&' characters, and return an error if there are more than one*/
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	/*Continue checking for errors by recursively calling the function with the next character*/
	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *i)
{

	/*Loop through the input string*/
	for (*i = 0; input[*i]; *i += 1)
	{

		/*If the current character is a space or a tab, skip it and continue the loop*/
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		/*If the current character is a special character (';', '|', or '&'), return -1 (error)*/
		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		/* If the current character is a non-space/tab character, exit the loop*/
		break;
	}

	/*Return 0 to indicate that no special character was found, and the index points to the first non-space/tab character*/
	return (0);
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @database: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error(data *database, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	/*Determine the specific syntax error message based on*/
	/*the character at index i*/
	if (input[i] == ';')
	{
		
		/*Handle the semicolon syntax error*/
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(database->counter);
	length = _strlen(database->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	/*Allocate memory for the error message*/
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}

	/*Copy strings and concatenate them to construct the error message*/
	_strcpy(error, database->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");


	/*Write the error message to the standard error stream*/
	write(STDERR_FILENO, error, length);

	/*Free the dynamically allocated memory*/
	free(error);
	free(counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @database: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data *database, char *input)
{
	/*Initialize the beginning index of the input*/
	int start = 0;

	/*Initialize a variable to hold the first character index*/
	int f_char = 0;

	/*Initialize a counter variable*/
	int i = 0;

	/*Find the index of the first non-whitespace character in the input*/
	f_char = first_char(input, &start);
	if (f_char == -1)
	{
		/* If no non-whitespace character is found*/
		/* print a syntax error and return 1*/
		print_syntax_error(database, input, start, 0);
		return (1);
	}

	/*Check for syntax errors related to separators or operators*/
	i = error_sep_op(input + start, 0, *(input + start));
	if (i != 0)
	{
		/*If a syntax error is found, print the error and return 1*/
		print_syntax_error(database, input, start + i, 1);
		return (1);
	}

	/*If no syntax errors are found, return 0*/
	return (0);
}
