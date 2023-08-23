#include "shell.h"
/* modified */
/**
 * err_num - like atoi
 * @s: str
 * Return: return 0 if no numbers to convert
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
 * print_error - puts an err msg
 * @info_params: struct containing shell params
 * @error_str: error str
*/
void print_error(info_s *info_params, char *error_str)
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
 * handle_comments - if # encountered , replace by a null term
 * @bbufer: the line_bbuferfer
 * Return: 0;
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
 * print_dec - prints a decimal
 * @nbr: the number to print
 * @file_dex: the file_dex to write to
 * Return: nbr of chars putted to the file
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
 * change_base - converts bases
 * @num: usually an int
 * @bas_de_nbr: this is the base of the nbr to convert
 * @the_flags: arg flgs
 * Return: a str
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


