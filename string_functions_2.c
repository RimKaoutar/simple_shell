#include "shell.h"

/**
 * strtow - splts a string
 * @stringss: input str
 * @d: delimiter
 * 
 * Description: Counts words and allocates array. Loops through string
 * tokenizing on delimiters and copying words into new strings.
 * 
 * Return: array of strs , or NULL
*/
char **strtow(char *stringss, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (stringss == NULL || stringss[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; stringss[i] != '\0'; i++)
		if (!is_delimiter(stringss[i], d) && (is_delimiter(stringss[i + 1], d) || !stringss[i + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimiter(stringss[i], d))
			i++;
		k = 0;
		while (!is_delimiter(stringss[i + k], d) && stringss[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = stringss[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * split_string - returns an array of strings originally separated by delims
 * @str: str
 * @separatorss: the separators
 * @wrd_cnt: word count
 * 
 * Description: Counts words and allocates array. Loops through string
 * tokenizing on delimiters and copying words into new strings.
 * 
 * Return: array of wrds
*/

char **split_string(char *str, char *separatorss, size_t *wrd_cnt)
{
	int v = 0, nbr_of_wds;
	char **wordds, *str_ptr = str;
	unsigned int c, wrd_size[MAX_WORD_COUNT];

	set_zeros(wrd_size, MAX_WORD_COUNT);
	nbr_of_wds = words_count(str, separatorss, wrd_size);

	if (nbr_of_wds == 0)
		return (NULL);
	wordds = malloc((sizeof(char *) * nbr_of_wds) + 1);
	if (!wordds)
		return (NULL);
	while (v < nbr_of_wds)
	{
		wordds[v] = malloc((sizeof(char) * wrd_size[v]) + 1);
		if (!wordds[v])
		{
			for (v--; v >= 0; v--)
				free(wordds[v]);
			free(wordds);
			return (NULL);
		}
		for (c = 0; c < wrd_size[v]; c++, str_ptr++)
		{
			while (is_delimiter(*str_ptr, separatorss))
				str_ptr++;

			wordds[v][c] = *str_ptr;
		};
		wordds[v][c] = '\0';
		v++;
	}
	*wrd_cnt = nbr_of_wds;
	wordds[v] = NULL;
	return (wordds);
}

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
