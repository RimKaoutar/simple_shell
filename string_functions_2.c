#include "shell.h"

/**
 * _strncpy - Copies a string from a source to a destination
 * @destination: The destination string
 * @source: The source string
 * @n: The maximum number of characters to copy
 * 
 * Description: Copies up to n characters of source string
 * to destination. Pads remaining dest with null bytes.
 * 
 * Return: A pointer to the destination string
*/ 
char *_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings
 * @destination: The destination string
 * @source: The source string to append
 * @n: The maximum number of chars to append
 * 
 * Description: Appends the source string to the dest string, 
 * concatenating the two. Truncates or null pads
 * if source is longer than n.
 * 
 * Return: A pointer to the destination string
*/
char *_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 * _strchr - Locates a character in a string
 * @str: The string to search
 * @c: The character to search for
 * 
 * Description: Searches string str for the first occurrence of
 * character c.
 * 
 * Return: A pointer to the occurrence of c in str, or NULL if c is
not found.
*/
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
