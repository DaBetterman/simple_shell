#include "shell.h"
/**
* _strncat - Concatenates two strings where n number
*            of bytes are copied from source.
* @dest: Pointer to destination string.
* @src: Pointer to source string.
* @n: n bytes to copy from src.
*
* Return: Pointer to destination string.
*/
char *_strncat(char *dest, const char *src, size_t n)
{
	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0' && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}

	*dest = '\0';

	return (dest);
}

/**
 * _strcmp - Function that compares two strings
 * @string1: first function
 * @string2: second function
 * Return: result of comparison
 */
int _strcmp(char *string1, char *string2)
{
	int comp = 0;

	while (*string1 == *string2 && *string1 != '\0')
	{
		string1++;
		string2++;
	}
	if (string1 != string2)
		comp = *string1 - *string2;

	return (comp);
}

/**
 * _strlen - length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}
