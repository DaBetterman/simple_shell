#include "shell.h"

/**
 * get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int get_len(int n)
{
	unsigned int n1;
	int lenght = 1;

/*Check if the integer is negative.*/
	if (n < 0)
	{
		/*Increment the length to account for the minus sign.*/
		lenght++;

		/*Make n1 positive for counting the digits.*/
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}

	/*Use a loop to count the digits by repeatedly dividing by 10.*/
	while (n1 > 9)
	{
		/*Increment the length for each digit.*/
		lenght++;

		/*Remove the last digit by dividing by 10.*/
		n1 = n1 / 10;
	}

	/*Return the calculated length of the integer.*/
	return (lenght);
}


/**
 * aux_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *aux_itoa(int n)
{
	unsigned int n1;

	/*Get the length of the integer.*/
	int lenght = get_len(n);

	char *buffer;

	/*Allocate memory for the string.*/
	buffer = malloc(sizeof(char) * (lenght + 1));

	/*Handle memory allocation failure.*/
	if (buffer == 0)
		return (NULL);

	/*Null-terminate the string.*/
	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		/*Handle negative numbers.*/
		n1 = n * -1;

		/*Place a minus sign at the beginning of the string.*/
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lenght--;
	do {
		/*Convert digits to characters.*/
		*(buffer + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	}
	/*Continue until all digits are processed.*/
	while (n1 > 0);


	/*Return the string representation of the integer.*/
	return (buffer);
}


/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	/*Iterate through the characters in the input string*/
	while (*(s + count) != '\0')
	{
		/*Check if the character is not a digit*/
		/*or if we've encountered non-digits after digits.*/
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		/*Check if the character is a minus sign, indicating a negative number.*/
		if (*(s + count) == '-')
			pn *= -1;

		/*If the character is a digit, adjust*/
		/*the multiplier and increment the size.*/
		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	/*Calculate the integer value from the string.*/
	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	/*Return the integer value, considering the sign.*/
	return (oi * pn);
}
