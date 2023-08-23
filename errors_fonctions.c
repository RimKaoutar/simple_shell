#include "shell.h"
/**
 * puts_err - Prints a string to stderr
 * @stringg: String to print
 * 
 * Description: Loops through the given string and prints each
 * character to stderr using putchar_err().
 * 
 * Return: Nothing.
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
 * putchar_err - Prints a character to stderr
 * @chhar: Character to print
 * 
 * Description: Uses a static buffer to collect characters
 * and flush to stderr when full or END is passed.
 * 
 * Return: 1 on success, -1 on error
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
 * write_char - Writes a character to a file descriptor
 * @chhar: Character to write
 * @file_desc: File descriptor
 * 
 * Description: Buffers characters in a static array and
 * flushes to the file descriptor when full or END passed.
 * 
 * Return: 1 on success, -1 on error
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
 * write_chars - Writes a string to a file descriptor
 * @sttring: String to write
 * @fd: File descriptor
 * 
 * Description: Loops through the string and writes each
 * character using write_char().
 * 
 * Return: Number of characters written

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
