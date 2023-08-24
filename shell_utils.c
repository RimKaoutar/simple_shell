#include "shell.h"

/**
 * err_num - Parses a string as an integer number
 * @s: String to parse
 *
 * Description:
 * Skips over leading '+' sign if present.
 * Loops through string, converting characters to digits.
 * Returns integer if fully digit string, else -1.
 * Checks for overflow against INT_MAX limit.
 *
 * Return: Converted integer or -1 on error
*/
int err_num(char *s)
{
	unsigned long int ress = 0;
	int ir = 0;

	if (*s == '+')
		s++;

	for (ir = 0; s[ir] != '\0'; ir++)
	{
		if (s[ir] >= '0' && s[ir] <= '9')
		{
			ress *= 10;
			ress += (s[ir] - '0');
			if (ress > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (ress);
}

/**
 * print_error - Prints an error message to standard error
 * @info_params: Info structure containing program details
 * @error_str: Error string message
 *
 * Description:
 * Prints the error message in the format:
 * <program_name>: <line_number>: <command>: <error_message>
 * By default, outputs to stderr. Used to display parse/runtime errors.
 *
 * Return: Nothing
*/
void print_error(shell_t *info_params, char *error_str)
{
	puts_err(info_params->prog_name);
	puts_err(": ");

	print_dec(info_params->lines, STDERR_FILENO);
	puts_err(": ");

	puts_err(info_params->argv[0]);
	puts_err(": ");

	puts_err(error_str);
}

/**
 * handle_comments - Strips comments from a command line
 * @bbufer: String containing command line
 *
 * Description:
 * Loops through the buffer checking for comment character.
 * If # is found at start of line or after space, it terminates
 * the string there to remove comments.
 *
 * Return: Nothing
*/

void handle_comments(char *bbufer)
{
	int i = 0;

	while (bbufer[i] != '\0')
	{
		if (bbufer[i] == '#' && (!i || bbufer[i - 1] == ' '))
		{
			bbufer[i] = '\0';
			break;
		}
		i++;
	}
}

/**
 * print_dec - Prints an integer as a decimal number
 * @nbr: Number to print
 * @file_dex: File descriptor to output to
 *
 * Description:
 * Handles negative numbers by converting to absolute value
 * Loops through places from billions to ones, outputting digits
 * Optionally outputs to stderr by passing STDERR_FILENO
 * Returns: Number of characters printed
 * This implements integer conversion to decimal for output.
 *
 * Return: Number of characters putted to the file
*/
int print_dec(int nbr, int file_dex)
{
	int (*__putchar)(char) = _putchar;
	int i;
	int compteur = 0;
	unsigned int absolute, courant;

	if (file_dex == STDERR_FILENO)
		__putchar = putchar_err;
	if (nbr < 0)
	{
		absolute = -nbr;
		__putchar('-');
		compteur++;
	}
	else
		absolute = nbr;
	courant = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{

		if (absolute / i)
		{
			__putchar('0' + courant / i);
			compteur++;
		}
		courant %= i;
	}
	__putchar('0' + courant);
	compteur++;
	return (compteur);
}
/**
 * change_base - Converts a number to a given numeric base
 * @num: Number to convert
 * @bas_de_nbr: Base to convert to (e.g. hex, oct)
 * @the_flags: Options like unsigned, lowercase
 *
 * Description:
 * Handles sign, makes number unsigned
 * Loops to extract digits in given base
 * Optionally makes output lowercase
 *
 * Return: Pointer to static buffer containing result
*/
char *change_base(long int num, int bas_de_nbr, int the_flags)
{
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	static char *tab;
	static char buf[50];

	if (!(the_flags & BAS_CHANGE_UNSIG) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	tab = the_flags & BAS_CHANGE_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';
	do {
		*--ptr = tab[n % bas_de_nbr];
		n /= bas_de_nbr;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
