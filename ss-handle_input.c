#include "shell.h"

/**
 * input_buf - intput fjk
 * @info: shell struct
 * @bufr: line buffer
 * @len: the length
 * Return: nbr of readed bytes
*/
ssize_t input_buf(info_s *info, char **bufr, size_t *len)
{
	ssize_t r = 0;
	size_t len_pp = 0;

	if (!*len)
	{
		free(*bufr);
		*bufr = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		r = getline(buf, &len_pp, stdin);
#else
		r = _getline(info, bufr, &len_pp);
#endif
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
 * read_buf - read
 * @info: the params strcut
 * @buf: the line buffer
 * @i: input
 * Return: the number
*/
ssize_t read_buf(info_s *info, char *bfuerr, size_t *i)
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
 * get_input - gets al ine
 * @info: the shell params
 * Return: bytes readed
*/
ssize_t get_input(info_s *info)
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
 * _getline - implementation of getline
 * @info: params struct
 * @pointeur: adrrr
 * @nobguerur: the lens
 * Return: s
*/
int _getline(info_s *info, char **pointeur, size_t *nobguerur)
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
 * handle_sigint - block control
 * @sig_num: sig
 * Return: none
*/
void handle_sigint(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");

	_putchar(NEG_ONE);
}
