#include "shell.h"
/**
 * from_terminal - Checks if input is coming from a terminal
 * @information: Info structure
 * Description: Checks if stdin file descriptor refers to a terminal
 * and input fd is less than or equal to standard file descriptors.
 * Indicates input is coming directly from user terminal.
 * 
 * Return: 1 if input is from terminal, 0 otherwise
*/
int from_terminal(shell_t *information)
{
	return (isatty(STDIN_FILENO) && information->fd_read <= 2);
}

/**
 * _isalpha - Checks for an alphabetic character
 * @chhar: Character to check
 * Description: Checks if the character is between 'a-z' or
 * 'A-Z' in the ASCII table, which are alphabetic characters.
 * 
 * Return: 1 if alphabetic, 0 otherwise
*/
int _isalpha(int chhar)
{
	if ((chhar >= 'a' && chhar <= 'z') || (chhar >= 'A' && chhar <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delimiter - Checks if a character is a delimiter
 * @chhar: The character to check
 * @dells: String of delimiter characters
 * Description: Loops through the delimiter characters and
 * returns True if the input character matches any delimiter.
 * 
 * Return: True if match found, False otherwise
*/
bool is_delimiter(char chhar, char *dells)
{
	int stringg;

	for (stringg = 0; dells[stringg]; stringg++)
		if (chhar == dells[stringg])
		{
			return (true);
		}
	return (false);
}

/**
 * _atoi - Converts a string to an integer
 * @stringg: Null terminated string to convert
 * 
 * Description: Loops through characters and multiplies/adds
 * to result if a digit. Handles sign. Returns signed integer.
 * 
 * Return: Converted integer value
*/
int _atoi(char *stringg)
{
	int i, sign = 1, flgg = 0;
	int otpot;
	unsigned int res = 0;

	for (i = 0; stringg[i] != '\0' && flgg != 2; i++)
	{
		if (stringg[i] == '-')
			sign *= -1;
		if (stringg[i] >= '0' && stringg[i] <= '9')
		{
			flgg = 1;
			res *= 10;
			res += (stringg[i] - '0');
		}
		else if (flgg == 1)
			flgg = 2;
	}
	if (sign == -1)
		otpot = -res;
	else
		otpot = res;
	return (otpot);
}
