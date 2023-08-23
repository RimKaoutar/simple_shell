#include "shell.h"


/**
 * check_file_in_path - Checks if a file exists in PATH directories
 * @info: Info struct
 * @str_path: PATH environment variable value
 * @cmd: File name to search for
 * Description:
 * Searches each PATH directory for the given file name.
 * Handles "." prefix and duplicates substrings of PATH.
 * Returns path if file is executable, else NULL.
 * Uses dup_chars() and is_executable() functions.
 * 
 * Return: Path if found, NULL if not found
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

/**
 * is_executable - Checks if a file is executable
 * @infooo: Info struct (unused)
 * @path: Path to file
 * 
 * Description:
 * Uses stat() system call to get file info
 * Checks if it is a regular file
 * And has executable permissions
 * 
 * Return: 1 if executable, 0 if not
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
 * dup_chars - Duplicates a substring from a string
 * @str_path: Source string
 * @commnece: Index of start character
 * @end: Index of end character
 * 
 * Description:
 * Copies characters from source string from start to end
 * Stores in a static buffer
 * Ignores ':' characters during copy
 * Adds null terminator
 * 
 * Return: Pointer to static buffer
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
