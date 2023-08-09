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

int _putchar(char c);
void _puts(char *s);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
int _strlen(char *s);


#endif
