#include "shell.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	/*Calculate the length of the input string*/
	len = _strlen(s);

	/*Allocate memory on the heap for the duplicated string*/
	new = malloc(sizeof(char) * (len + 1));

	/*Check if memory allocation was successful*/
	if (new == NULL)
	{
		return (NULL);
	}

	/*Copy the input string 's' to the newly allocated memory*/
	_memcpy(new, s, len + 1);

	/*Return a pointer to the duplicated string in the heap*/
	return (new);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int len;


	/*Initialize 'len' to 0 and iterate through the string until the null terminator is reached*/
	for (len = 0; s[len] != 0; len++)
	{
		/*Count the characters in the string*/
	}

	/*Return the length of the string*/
	return (len);
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if all characters in 'str' are equal to any character in 'delim', 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}

	/*If all characters in 'str' match any character in 'delim', return 1*/
	if (i == k)
		return (1);

	/*If there is at least one character that doesn't match, return 0*/
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	/*If str is not NULL, it's the first call for this string*/
	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		i = _strlen(str);
		str_end = &str[i]; /*Store last address*/
	}
	str_start = splitted;

	/*If we've reached the end of the string, return NULL*/
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replace the delimiter with a null character '\0'*/
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}

		/*If bool is 0 and *splitted is not empty, set bool to 1*/
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}

	/*If bool is still 0, the string is equal to the delimiter, so return NULL*/
	if (bool == 0)
		return (NULL);

	/*Return a pointer to the next token in the string*/
	return (str_start);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	/*Iterate through the characters in the string*/
	for (i = 0; s[i]; i++)
	{
		/*Check if each character is a digit (0 to 9) by comparing its ASCII value*/
		if (s[i] < 48 || s[i] > 57)

			/*If any character is not a digit, return 0*/
			return (0);
	}
	/*If all characters are digits, return 1 to indicate it's a number*/
	return (1);
}
