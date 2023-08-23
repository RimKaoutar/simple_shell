#include "shell.h"
/* modified */
/**
 * is_executable - checks if executable or not
 * @infooo: info strct
 * @path: the path
 * Return: 1 or 0
*/
bool is_executable(info_s *infooo, char *path)
{
	struct stat statisi;

	(void)infooo;
	if (!path || stat(path, &statisi))
		return (0);

	if (statisi.st_mode & S_IFREG)
		return (true);
	return (false);
}

/**
 * dup_chars - dups chars
 * @str_path: path
 * @commnece: the commneceinlg idx
 * @end: the end
 * Return: pointer to new buffer
*/
char *dup_chars(char *str_path, int commnece, int end)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = commnece; i < end; i++)
		if (str_path[i] != ':')
			buffer[k++] = str_path[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * check_file_in_path - looks for the cmd in the PATH variabl
 * @info: strct info for params of shell
 * @str_path: str of path
 * @cmd: command to check
 * Return: either path or NULL
*/
char *check_file_in_path(info_s *info, char *str_path, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *pathh;

	if (!str_path)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			pathh = dup_chars(str_path, curr_pos, i);
			if (!*pathh)
				_strcat(pathh, cmd);
			else
			{
				_strcat(pathh, "/");
				_strcat(pathh, cmd);
			}
			if (is_executable(info, pathh))
				return (pathh);
			if (!str_path[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
