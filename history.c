#include "shell.h"

/**
 * read_hist - reads the hyst
 * @infor: strcut info
 *
 * Description:
 * Gets the HOME enviroment variable to determine base path.
 * Allocates a new string large enough to hold the full path.
 * Concatenates the directory, file separator, and file name.
 * Returns the path string. Caller is responsible for freeing.
 *
 * Return: a string with  hystory
*/
char *read_hist(shell_t *infor)
{
	char *bufferr, *directory;

	directory = _getenv(infor, "HOME=");
	if (!directory)
		return (NULL);
	bufferr = malloc(sizeof(char) *
			(_strlen(directory) + _strlen(HIST_FILE_NAME) + 2));
	if (!bufferr)
	{
		return (NULL);
	}
	bufferr[0] = 0;
	_strcpy(bufferr, directory);
	_strcat(bufferr, "/");
	_strcat(bufferr, HIST_FILE_NAME);
	return (bufferr);
}

/**
 * create_history - creats a file containing hystory
 * @informm: the struct for the params of the shell
 *
 * Description:
 * Opens the history file in create/truncate mode.
 * Writes each history entry string followed by newline.
 * Writes EOF character and closes file.
 * Frees memory used for file path.
 *
 * Return: 1 and -1
*/
int create_history(shell_t *informm)
{
	ssize_t file_desc;
	char *file_nm = read_hist(informm);
	list_t *neud = NULL;

	if (!file_nm)
		return (-1);

	file_desc = open(file_nm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_nm);
	if (file_desc == -1)
		return (-1);
	for (neud = informm->history; neud; neud = neud->next)
	{
		write_chars(neud->str, file_desc);
		write_char('\n', file_desc);
	}
	write_char(NEG_ONE, file_desc);
	close(file_desc);
	return (1);
}

/**
 * renumber_history - updates the number of hystory lines
 * @struct_info: the hystory container
 *
 * Description:
 * Traverses the history linked list and renumbers each entry.
 * Sets the hist_lines field to the total number of entries.
 *
 * Return: hystory line newly renumbered
*/
int renumber_history(shell_t *struct_info)
{
	int i = 0;
	list_t *neud = struct_info->history;

	for (; neud; neud = neud->next)
		neud->num = i++;
	return (struct_info->hist_lines = i);
}

/**
 * read_history - reads hystory
 * @innfor: a struct containing params of the shell
 *
 * Description:
 * Opens the history file and reads contents into a buffer.
 * Parses buffer by newline and calls update_history.
 * Renumbers and truncates history as needed.
 *
 * Return: hystory line , on failiure 0
*/
int read_history(shell_t *innfor)
{
	int i, dernier = 0;
	int line_counter = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *file_name = read_hist(innfor);

	if (!file_name)
		return (0);
	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			update_history(innfor, buf + dernier, line_counter++);
			dernier = i + 1;
		}
	if (dernier != i)
		update_history(innfor, buf + dernier, line_counter++);
	free(buf);
	innfor->hist_lines = line_counter;
	while (innfor->hist_lines-- >= HIST_SIZE_MAX)
		delete_node_at_index(&(innfor->history), 0);
	renumber_history(innfor);
	return (innfor->hist_lines);
}

/**
 * update_history - Updates the history of a linked list
 * @infoe: Info structure to update
 * @baffer: Line string to add
 * @line_c: Line number
 *
 * Description:
 * Checks if history already exists, gets tail pointer.
 * Adds new node to end of list using line string and number.
 * Sets history head if not already set.
 *
 * Return: 0
*/
int update_history(shell_t *infoe, char *baffer, int line_c)
{
	list_t *neud = NULL;

	if (infoe->history)
		neud = infoe->history;

	add_node_end(&neud, baffer, line_c);

	if (!infoe->history)
	{
		infoe->history = neud;
	}
	return (0);
}
