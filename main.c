#include "main.h"

/**
 * printPrompt - Function prints the prompt only when in interactive mode
 */
void printPrompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 3);
		fflush(stdout);
	}
}

/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: An array of argument variables
 * @env: Environment variables
 * Return: 0 (Success)
 */
int main(int argc, char **argv, char **env)
{
	(void)argc;
	while (true)
	{
		char *userInput;
		char **commandTokens;
		int i;

		i = 0;

		printPrompt();
		userInput = readInput();

		if (strcmp(userInput, "exit\n") == 0)
		{
			free(userInput);
			exit(EXIT_SUCCESS);
		}

		if (strcmp(userInput, "env\n") == 0)
		{
			free(userInput);
			while (env[i] != NULL)
			{
				printf("%s\n", env[i]);
				i++;
			}
		}
		commandTokens = inputToTokenArr(userInput);
		if (commandTokens == NULL)
		{
			free(commandTokens);
		}
		if (commandTokens[0] != NULL)
		{
			executeCommand(commandTokens, env, argv);
		}
		freeTokens(commandTokens);
		free(userInput);
	}
	return (0);
}
