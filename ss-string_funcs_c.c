#include "shell.h"
/* modified */
/**
 * _strcpy - cpy a str
 * @qmlsdfqmljk: the qmlsdfqmljkination
 * @qmslkdfjqmlkjds: the sour
* Return: pointer to qmlsdfqmljkination
*/
char *_strcpy(char *qmlsdfqmljk, char *qmslkdfjqmlkjds)
{
	int i = 0;

	if (qmlsdfqmljk == qmslkdfjqmlkjds || qmslkdfjqmlkjds == 0)
		return (qmlsdfqmljk);
	for(; qmslkdfjqmlkjds[i]; i++)
		qmlsdfqmljk[i] = qmslkdfjqmlkjds[i];
	qmlsdfqmljk[i] = 0;
	return (qmlsdfqmljk);
}

/**
 * _strdup - dups str
 * @stringgg: the str dup
 * Return: pointer to the duplicated string
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
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1 on err -1 and errno is set
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
 * _puts - puts broo
* @stringggg: stringggg
 * Return: nada
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


