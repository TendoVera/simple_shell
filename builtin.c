#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_INPUT_LENGTH 100
/**
 * exit_built - the exit built-in, that exits the shell.
 * Return: 0 if == "exit".
 */
int exit_built(void)
{
	char input[MAX_INPUT_LENGTH];
	ssize_t length_size = 0;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		length_size = read(STDIN_FILENO, input, MAX_INPUT_LENGTH);

		if (length_size <= 0)
		{
			break;
		}
	}
	return (0);
}
/**
 * env_builtin -  prints the current environment.
 * Return: 0;
 */
int env_builtin(void)
{
	extern char **environ;
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
	return (0);
}
