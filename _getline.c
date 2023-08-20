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
 * _getline - gets a line of input from the user.
 *
 * @str - A pointer to the buffer that will store the input line.
 * @n - The maximum number of characters that can be stored in the buffer.
 * Returns:
 *   A pointer to the buffer that contains the input line.
 */
ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
	char *buff = NULL;
	size_t buff_size = 0, len_read = 0;
	char c;

	if (lineptr == NULL || n == NULL || stream == NULL)
	{
		return (-1);
	}
	if (*lineptr == NULL)
	{
		*lineptr = malloc(*n * sizeof(char));
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}
	buff = *lineptr;
	buff_size = *n;

	while ((c = _getchar() != EOF))
	{
		if (len_read + 1 >= buff_size)
		{
			buff_size += 128;
			buff = _realloc(buff, *n, buff_size);
			if (buff == NULL)
			{
				free(buff);
				return (-1);
			}
		}
		buff[len_read++] = c;
		if (c == '\n')
		{
			break;
		}
	}
	if (len_read == 0)
	{

		free(buff);
		return (-1);
	}
	buff[len_read] = '\0';
	*lineptr = buff;
	*n = buff_size;
	return (len_read);
}
