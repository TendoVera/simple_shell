#include "shell.h"
/**
* prompt_line - Entry.
* Return: 0.
*/
int prompt_line(void);
int prompt_line(void)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	int arg_count = 0;
	char *token, *fl_path;
	int pin;
	ssize_t size_length = 0;
	char *args[MAX_ARGS];
	pid_t c_pid;
	char input[MAX_INPUT_LENGTH];
	struct stat s;

	while (1)
	{
		write(STDOUT_FILENO, "Tendo$ ", 7);
		size_length = read(STDIN_FILENO, input, MAX_INPUT_LENGTH);

	if (size_length == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		continue;
	}

	input[size_length - 1] = '\0';
	if (_strcmp(input, "exit") == 0)
	{
		break;
	}


	for (token = strtok(strdup(path_copy), ":");
	token != NULL;
	token = strtok(NULL, ":"))
	{
		fl_path = malloc(strlen(token) + strlen(input) + 2);
		sprintf(fl_path, "%s/%s", token, input);

		if (stat(fl_path, &s) == 0 && s.st_mode & S_IXUSR)
		{
			break;
		}

		free(fl_path);
	}

	if (token == NULL)
	{
		write(STDERR_FILENO, "Error: Command not found or not executable.\n", 43);
		continue;
	}

	arg_count = parse_arguments(input, args);

	c_pid = fork();

	if (c_pid < 0)
	{
		write(STDERR_FILENO, "Fork error.\n", 12);
		break;
	}
	else if (c_pid == 0)
	{
		args[arg_count] = NULL;
		if (execve(fl_path, args, NULL) == -1)
		{
			perror("execve");
			free(fl_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(c_pid, &pin, 0);
		free(fl_path);
	}
}

	free(path_copy);
	return (0);
}
/**
* parse_arguments - is extract an argument and command input.
* @input: command line input.
* @args: an array of strings.
* Return: arg_count (total number of arguments.
*/
int parse_arguments(char *input, char **args)
{
	int arg_count = 0;
	char *token;

	token = strtok(input, " \n");

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " \n");
	}
	args[arg_count] = NULL;
	return (arg_count);
}
