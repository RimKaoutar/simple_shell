#include "shell.h"
/**
 * words_count - Counts the number of words in a string.
 * @s: The string to count words in.
 * @delim: The delimiter characters to use for separating words.
 * @ptr: A pointer to an unsigned int array to store the lengths of words.
 *
 * Return: The number of words counted.
 */

int words_count(char *s, char *delim, unsigned int *ptr)
{
	char *str = s;
	bool go = false, delimiter;
	unsigned int i = 0, j = 0, cnt = 0, len = 1;

	if (!s)
		return (0);

	while (!go)
		while (delim[i])
		{
			if (*str == delim[i])
				str++;
			else
				go = true;
			i++;
		}

	if (!*(str + 1))
	{
		ptr[0] = 1;
		return (1);
	}

	while (str[j])
	{
		delimiter = is_delimiter(str[j], delim);

		if (delimiter && !(is_delimiter(str[j - 1], delim)))
		{
			ptr[cnt] = len;
			cnt++;
		}

		if ((!str[j + 1]) && !delimiter)
		{
			len++;
			ptr[cnt] = len;
			cnt++;
			break;
		}

		if (!delimiter)
			len++;
		else
			len = 0;
		j++;
	}

	return (cnt);
}
