#include "shell.h"

/*
 * This function gets a line of input from the user.
 *
 * @str - A pointer to the buffer that will store the input line.
 * @n - The maximum number of characters that can be stored in the buffer.
 * Returns:
 *   A pointer to the buffer that contains the input line.
 */
char *_getline(char *str, int n)
{
	int i = 0;
	int c = getchar();

	while (c != EOF && c != '\n')
	{
		str[i] = c;
		i++;
		c = getchar();
	}
	if (c == '\n')
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return str;
}
