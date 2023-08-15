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

/* executionners */
void executionner(ssize_t, char *, int);
void exec1(ssize_t, char *);

#endif
