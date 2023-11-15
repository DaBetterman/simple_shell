#include "shell.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	/*Calculate the length of the*/
	/*string by counting characters until the null terminator '\0'*/
	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}

	/*Set a pointer 'str' to the input string 's'*/
	str = s;

	/*Loop to reverse the string*/
	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{

			/*Swap characters in the string to reverse it*/
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
