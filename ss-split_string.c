#include "shell.h"
/* modified */

/**
 * 
 * split_string - Splits a string into tokens based on a delimiter
 * @str: The string to split
 * @delimiter: The delimiter characters
 * @cnt: Pointer to store number of tokens
 * 
 * Return: Pointer to 2D array of tokens or NULL on failure
*/
char **split_string(char *str, char *delimeter, size_t *cnt)
{
	int i = 0, num;
	unsigned int j = 0, size[MAX_WORD_COUNT];
	char **line, *str_ptr = str;

	set_zeros(size, MAX_WORD_COUNT);
	num = words_count(str, delimeter, size);

	if (num == 0)
		return (NULL);

	line = malloc((sizeof(char *) * num) + 1);
	if (!line)
		return (NULL);

	while (i < num)
	{
		line[i] = malloc((sizeof(char) * size[i]) + 1);
		if (!line[i])
		{
			while (i-- >= 0)
			{
				free(line[i]);
			}
			free(line);
			return (NULL);
		}

		while (j < size[i])
		{
			while (is_delimiter(*str_ptr, delimeter))
			{
				str_ptr++;
			}
			line[i][j] = *str_ptr;
			j++;
			str_ptr++;
		};

		line[i][j] = '\0';
		i++;
	}

	*cnt = num;

	line[i] = NULL;

	return (line);
}

/**
 * strtow - Splits a string into words based on a delimiter
 * @str: The string to split
 * @delimiter: The delimiter characters (default is space)
 * 
 * Return: Pointer to 2D array of words or NULL on failure
*/

char **strtow(char *str, char *delimeter)
{
	char **s;
	int i = 0, j = 0, k = 0, l = 0, num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!delimeter)
		delimeter = " ";

	while (str[i] != '\0')
	{
		if (!is_delimiter(str[i], delimeter) && (is_delimiter(str[i + 1], delimeter) || !str[i + 1]))
			num++;
		i++;
	}
	if (num == 0)
		return (NULL);
		
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);

	i = 0;
	while (j < num)
	{
		while (is_delimiter(str[i], delimeter))
		{
			i++;
		}
		k = 0;
		while (!is_delimiter(str[i + k], delimeter) && str[i + k])
		{
			k++;
		}
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			k = 0;
			while (k < j)
			{
				free(s[k]);
				k++;
			}
			free(s);
			return (NULL);
		}

		while (l < k)
		{
			s[j][l] = str[i++];
			l++;
		}
		s[j][l] = 0;
		j++;
	}
	s[j] = NULL;
	return (s);
}
