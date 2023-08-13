#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* string_funtions_1 */
int _putchar(char);
int _puts(char *);
char *_strcat(char *, char *);
char *_strncat(char *, char *, int );
int _strlen(char *);
/* string_funtions_2 */
int _strcmp(char *, char *);

/* get_functions*/

/**
 * getline_return - the getline function does not return only the number of chars
 * printed, put also changes the line_buffer that got those chars from stdin
 * therefor , using the funcion "putline" , we will return this struct
 * @line_buff: the line_buffer used by getline in the function "putline"
 * @charsnbr: the number of chars printed to stdin by getline
*/
typedef struct getline_return
{
	char *line_buff;
	size_t charsnbr;
}getline_return;
getline_return* putline(getline_return *);
char *_getenv(const char *);
char **get_args(char *);
char *get_command(char *path, char *cmd);

#endif
