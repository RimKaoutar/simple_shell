#include "shell.h"

/**
 * input_buf - Reads input into a buffer from user
 * @info: Info struct containing shell data
 * @bufr: Pointer to buffer pointer
 * @len: Length of buffer
 * 
 * Description:
 * If buffer not allocated, frees existing and allocates
 * Calls _getline() to read input into buffer
 * Handles newline, comments, history updating
 * Returns buffer and length on success
 * 
 * Return: Number of bytes read or -1 on error
*/
ssize_t input_buf(shell_t *info, char **bufr, size_t *len)
{
	ssize_t r = 0;
	size_t len_pp = 0;

	if (!*len)
	{
		free(*bufr);
		*bufr = NULL;
		signal(SIGINT, handle_sigint);
		r = _getline(info, bufr, &len_pp);
		if (r > 0)
		{
			if ((*bufr)[r - 1] == '\n')
			{
				(*bufr)[r - 1] = '\0';
				r--;
			}
			info->lc_flag = 1;
			handle_comments(*bufr);
			update_history(info, *bufr, info->hist_lines++);
			{
				*len = r;
				info->sep_buff = bufr;
			}
		}
	}
	return (r);
}
/**
 * read_buf - Reads input from file into a buffer
 * @info: Info struct with file descriptor
 * @bfuerr: Buffer to read into
 * @i: Size of buffer
 * 
 * Description:
 * Reads up to BUFFER_SIZE bytes from file
 * Stores number of bytes read into size variable
 * 
 * Return: Number of bytes read or -1 on errorread_buf - read
*/
ssize_t read_buf(shell_t *info, char *bfuerr, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->fd_read, bfuerr, BUFFER_SIZE_READ);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * get_input - Gets input from user or file into argv
 * @info: Info struct with input source
 * 
 * Description:
 * Calls input_buf() to read input into static buffer
 * Parses buffer into argv array separated by ;|&
 * Handles multiple logical command lines in buffer
 * 
 * Return: length of parsed argv string or -1 on error
*/
ssize_t get_input(shell_t *info)
{
	static char *bufr;
	static size_t i, j, len;
	ssize_t r = 0;
	char **bufer_pointer = &(info->arg), *p;

	_putchar(NEG_ONE);
	r = input_buf(info, &bufr, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = bufr + i;

		check_chain(info, bufr, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, bufr, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->sep_buff_kind = REG_FLAG;
		}
		*bufer_pointer = p;	
		return (_strlen(p));
	}
	*bufer_pointer = bufr;
	return (r);
}

/**
 * _getline - Reads input into a buffer with dynamic allocation
 * @info: Info struct with input source
 * @pointeur: Pointer to buffer pointer
 * @nobguerur: Size of buffer
 * 
 * Description:
 * Reads input from source into static buffer
 * Reallocates and concatenates to passed buffer pointer
 * Handles buffer resizing across multiple calls
 * 
 * Return: number of bytes read or -1 on error
*/
int _getline(shell_t *info, char **pointeur, size_t *nobguerur)
{
	static char buf[BUFFER_SIZE_READ];
	static size_t i, nong;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *pointer_n = NULL, *c;

	p = *pointeur;
	if (p && nobguerur)
		s = *nobguerur;
	if (i == nong)
		i = nong = 0;

	r = read_buf(info, buf, &nong);
	if (r == -1 || (r == 0 && nong == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : nong;
	pointer_n = _realloc(p, s, s ? s + k : k + 1);
	if (!pointer_n)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(pointer_n, buf + i, k - i);
	else
		_strncpy(pointer_n, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = pointer_n;

	if (nobguerur)
		*nobguerur = s;
	*pointeur = p;
	return (s);
}

/**
 * handle_sigint - Handles SIGINT interrupt signal
 * @sig_num: Signal number (unused)
 * 
 * Description:
 * Prints a newline followed by prompt when SIGINT received
 * SIGINT is triggered by Ctrl-C
 * Simply resets prompt to continue input
 * Return: Nothing.
*/
void handle_sigint(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");

	_putchar(NEG_ONE);
}
