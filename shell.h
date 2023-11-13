#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_C 10

/**
 * struct denum - structure that contains vars
 * @cnt: lines cnt
 */
typedef struct denum
{
	int cnt;
} denum;

void prompt(int arc, char **arv, char **envp, bool interactive);
int _strcmp(char *string1, char *string2);
char *_strcat(char *dest, char *src);
char *handle_path(char **token, char *cmd);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
void handle_exit(char *cmd);
void execution(char **token, char **arv, char **envp);
char *white_space(char *cmd);
char *_strncpy(char *dest, char *src, int n);
void geterror(denum *n, char **arv, char *cmd);
void check_active(int arc, char **arv, char **envp);
char *_getenv(const char *name, char **_environ);
extern char **environ;

#endif
