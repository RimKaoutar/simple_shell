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
char **splitstr(char *);
char *_strcpy(char *, char *);
char *_strdup(char *);

/* executionners */
void executionner(ssize_t, char *, int, char **);
void exec1(ssize_t, char *);
void exec2(ssize_t, char *);
void exec3(ssize_t, char *, char **);

/* _realloc */
void *_realloc(void *, unsigned int, unsigned int);

/* path_handling_functions */
char *_getenv(const char *, char **);
char *get_command(char *, char **);
void print_env(char **);
int checker(char *, char **);

/* _getline*/
char *_getline(char*, int);

#endif
