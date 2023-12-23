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

while (1)
{
write(STDOUT_FILENO, "$ ", 2);
size_length = read(STDIN_FILENO, input, MAX_INPUT_LENGTH);

if (_strcmp(input, "exit") == 0)
{
exit(0);
}

if (size_length == 0)
{
write(STDOUT_FILENO, "\n", 1);
break;
}
else if (size_length < 0)
{
write(STDERR_FILENO, "Error reading input.\n", 21);

continue;
}
arg_count = parse_arguments(input, args);

if (arg_count > 0)
{
c_pid = fork();

if (c_pid < 0)
{
write(STDERR_FILENO, "Fork error.\n", 29);

continue;
}
else if (c_pid == 0)
{
token = strtok(path_copy, " ");

while (token != NULL)
{
fl_path = malloc(_strlen(token) + 2);
sprintf(fl_path, "%s", token);
args[MAX_ARGS] = NULL;

if (execve(fl_path, args, NULL) == -1)
{
perror("execve");
free(fl_path);
exit(EXIT_FAILURE);
}
free(fl_path);
token = strtok(NULL, " ");
}
write(STDERR_FILENO, "Error occurred for command.\n", 29);
exit(EXIT_FAILURE);
}
else
{
waitpid(c_pid, &pin, 0);
}
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
