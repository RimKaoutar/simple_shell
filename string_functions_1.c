#include "shell.h"

/**
 * _strcpy - Copies the string pointed to by source into
 * the array pointed to by destination
 * @destination: A pointer to the destination array where the
 * content is to be copied
 * @source: A pointer to the source of data to be copied
 * 
 * Description: The _strcpy function copies the string pointed
 * to by source (including the terminating null character) into
 * the array pointed to by destination.
 * 
 * Return: A pointer to the destination array
*/
char *_strcpy(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == 0)
		return (destination);
	for(; source[i]; i++)
		destination[i] = source[i];
	destination[i] = 0;
	return (destination);
}

/**
 * _strdup - Duplicates a string
 * @stringgg: Source string to duplicate
 * 
 * Description: Counts the length of the source string
 * and allocates memory for a copy. Copies the characters
 * backwards to maintain proper null-termination.
 * 
 * Return: Pointer to a new allocated string containing a copy
 * of the string, or NULL if insufficient memory
*/
char *_strdup(const char *stringgg)
{
	int lenss = 0;
	char *ret;

	if (stringgg == NULL)
		return (NULL);
	while (*stringgg++)
		lenss++;
	ret = malloc(sizeof(char) * (lenss + 1));

	if (!ret)
		return (NULL);
	for (lenss++; lenss--;)
		ret[lenss] = *--stringgg;
	return (ret);
}

/**
 * _putchar - Outputs a character to stdout
 * @c: The character to output
 * 
 * Description: Uses a static buffer to collect characters
 * and flush to stdout when full or END is passed.
 * 
 * Return: 1 on success, -1 on error
*/
int _putchar(char c)
{
	static int i;
	static char buffer[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buffer[i++] = c;
	return (1);
}

/**
 * _puts - Outputs a string to stdout
 * @stringggg: The string to output
 * 
 * Description: Loops through the input string and outputs
 * each character using _putchar().
 * 
 * Returns: Nothing.
*/
void _puts(char *stringggg)
{
	int i = 0;

	if (!stringggg)
	{
		return;
	}
	while (stringggg[i] != '\0')
	{
		_putchar(stringggg[i]);
		i++;
	}
}
