#include "shell.h"
/* modified */
/**
 * from_terminal - sees if stdin was redirected
 * @information: struct address
 * Return: 1 if from_terminal mode else 0
*/
int from_terminal(info_s *information)
{
	return (isatty(STDIN_FILENO) && information->fd_read <= 2);
}

/**
 * _isalpha - checks for if the c is alpha
 * @chhar: the char
 * Return:  10 
*/
int _isalpha(int chhar)
{
	if ((chhar >= 'a' && chhar <= 'z') || (chhar >= 'A' && chhar <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delimiter - sees if delimiter
 * @chhar: char
 * @dells: the str
 * Return: true or false
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
 * _atoi - string to int
 * @stringg: str
 * Return: if nothing to convert 0
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
