#include "shell.h"

/*
 * _getchar - reads a single character from stdin
 *
 * Return: The character read from stdin if successful, EOF otherwise
*/
int _getchar(void)
{
	int c;
	ssize_t len_read;

	len_read = read(STDIN_FILENO, &c, 1);
	if (len_read == -1) {
		perror("getchar");
		return EOF;
	}
	if (len_read == 0) {
		return EOF;
	}

	return c;
}
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

	(void)n;
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
