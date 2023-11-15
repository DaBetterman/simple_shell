#include "shell.h"

/**
 * _strcat - concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	/*Find the null terminator in 'dest' to determine its end*/
	for (i = 0; dest[i] != '\0'; i++)
	{

	}

	/*Iterate through the characters in 'src' and append them to 'dest'*/
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	/*Add a null terminator to the end of the concatenated string*/
	dest[i] = '\0';

	/*Return a pointer to 'dest'*/
	return (dest);
}


/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t a;

	/*Iterate through the characters of 'src' and copy them to 'dest'*/
	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}

	/*Add the null terminator '\0' to the*/
	/*end of 'dest' to terminate the copied string*/
	dest[a] = '\0';

	/*Return a pointer to 'dest'*/
	return (dest);
}


/**
 * _strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	/*Iterate through the characters of both strings*/
	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
	{
		/*Continue comparing characters as*/
		/*long as they are equal and not the null terminator*/
	}

	/*Compare the characters at the current position*/
	/*If s1's character is greater, return 1*/
	if (s1[i] > s2[i])
		return (1);

	/*If s2's character is greater, return -1*/
	if (s1[i] < s2[i])
		return (-1);

	/*If both strings are equal, return 0*/
	return (0);
}


/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	/*Iterate through the characters in the 's' string*/
	for (; *(s + i) != '\0'; i++)

		/*If the current character matches 'c', return a pointer to that character*/
		if (*(s + i) == c)
			return (s + i);

	/*If the character 'c' is found at the end of*/
	/*the string, return a pointer to it*/
	if (*(s + i) == c)
		return (s + i);

	/*If 'c' is not found in the string, return a pointer to NULL ('\0')*/
	return ('\0');
}


/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int i, j, bool;

	/*Iterate through the characters in the "s" string*/
	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;

		/*Iterate through the characters in the "accept" string*/
		for (j = 0; *(accept + j) != '\0'; j++)
		{

			/*If a character in "s" matches a character*/
			/*in "accept," set bool to 0 and break*/
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}

		/*If bool is still 1, no match was found, so break the loop*/
		if (bool == 1)
			break;
	}
	/*Return the number of accepted bytes (length of the prefix substring)*/
	return (i);
}
