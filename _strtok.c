#include "shell.h"
/**
 * check_delim - Checks If A Character Match Any Char
 * @c: Char
 * @str: Stri
 * Return: 1
 */
unsigned int check_delim(char c, char *str)
{
	unsigned int index;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (c == str[index])
			return (1);
	}
	return (0);
}

/**
 * _strtok - Token A String Into Token (strtrok)
 * @str: Str
 * @delim: delimiter
 * Return: Pointer To The
 */
char *_strtok(char *str, char *delim)
{
	static char *qmsdlkfjqmsldk;
	static char *nt;
	unsigned int i;

	if (str != NULL)
		nt = str;
	qmsdlkfjqmsldk = nt;
	if (qmsdlkfjqmsldk == NULL)
		return (NULL);
	for (i = 0; qmsdlkfjqmsldk[i] != '\0'; i++)
	{
		if (check_delim(qmsdlkfjqmsldk[i], delim) == 0)
			break;
	}
	if (nt[i] == '\0' || nt[i] == '#')
	{
		nt = NULL;
		return (NULL);
	}
	qmsdlkfjqmsldk = nt + i;
	nt = qmsdlkfjqmsldk;
	for (i = 0; nt[i] != '\0'; i++)
	{
		if (check_delim(nt[i], delim) == 1)
			break;
	}
	if (nt[i] == '\0')
		nt = NULL;
	else
	{
		nt[i] = '\0';
		nt = nt + i + 1;
		if (*nt == '\0')
			nt = NULL;
	}
	return (qmsdlkfjqmsldk);
}