/* modified */
#include "shell.h"
/**
 * puts_err - puts an error
 * @stringg: the stringging to be printed
 * Return: nada
*/
void puts_err(char *stringg)
{
	int index = 0;

	if (!stringg)
		return;
	while (stringg[index] != '\0')
	{
		putchar_err(stringg[index]);
		index++;
	}
}
/**
 * putchar_err - puts a char to stderr
 * @chhar: c
 * Return: success 1 , fail -1
*/
int putchar_err(char chhar)
{
	static int i;
	static char bufferr[BUFFER_SIZE_WRITE];

	if (chhar == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(2, bufferr, i);
		i = 0;
	}
	if (chhar != NEG_ONE)
		bufferr[i++] = chhar;
	return (1);
}
/**
 * write_char - write a c
 * @chhar: char
 * @file_desc: the fd
 * Return: success = 1
*/
int write_char(char chhar, int file_desc)
{
	static int i;
	static char buffer[BUFFER_SIZE_WRITE];

	if (chhar == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(file_desc, buffer, i);
		i = 0;
	}

	if (chhar != NEG_ONE)
		buffer[i++] = chhar;
	return (1);
}
/**
 * write_chars - print
 * @sttring: the sttringing to be printed
 * @fd: the fd
 * Return: the number of chars put
*/
int write_chars(char *sttring, int fd)
{
	int i = 0;

	if (!sttring)
	{
		return (0);
	}
	while (*sttring)
	{
		i += write_char(*sttring++, fd);
	}
	return (i);
}
