#include "shell.h"
/* modified */


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
	unsigned int i, j, len = 1;
	unsigned int cnt = 0;
	char *str = s;
	bool go = false, delimiter;

	if (!s)
		return (0);

	while (!go)
		for (j = 0; delim[j]; j++)
		{
			if (*str == delim[j])
				str++;
			else
				go = true;
		}

	if (!*(str + 1))
	{
		ptr[0] = 1;
		return (1);
	}

	for (i = 1; str[i]; i++)
	{
		delimiter = is_delimiter(str[i], delim);

		if (delimiter && !(is_delimiter(str[i - 1], delim)))
		{
			ptr[cnt] = len;
			cnt++;
		}

		if ((!str[i + 1]) && !delimiter)
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
	}

	return (cnt);
}
