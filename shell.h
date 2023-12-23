#ifndef _SHELL_H_
#define _SHELL_H_
#define MAX_ARGS 64
#define MAX_INPUT_LENGTH 100
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
int betty_check(int x, int y);
int prompt_line(void);
int exit_built(void);
int _strlen(char *s);
int _strcmp(const char *str1, const char *str2);
int parse_arguments(char *input, char **args);
#endif
