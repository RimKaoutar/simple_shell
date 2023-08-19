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
	static char *niterror;
	unsigned int i;

	if (str != NULL)
		niterror = str;
	qmsdlkfjqmsldk = niterror;
	if (qmsdlkfjqmsldk == NULL)
		return (NULL);
	for (i = 0; qmsdlkfjqmsldk[i] != '\0'; i++)
	{
		if (check_delim(qmsdlkfjqmsldk[i], delim) == 0)
			break;
	}
	if (niterror[i] == '\0' || niterror[i] == '#')
	{
		niterror = NULL;
		return (NULL);
	}
	qmsdlkfjqmsldk = niterror + i;
	niterror = qmsdlkfjqmsldk;
	for (i = 0; niterror[i] != '\0'; i++)
	{
		if (check_delim(niterror[i], delim) == 1)
			break;
	}
	if (niterror[i] == '\0')
		niterror = NULL;
	else
	{
		niterror[i] = '\0';
		niterror = niterror + i + 1;
		if (*niterror == '\0')
			niterror = NULL;
	}
	return (qmsdlkfjqmsldk);
}