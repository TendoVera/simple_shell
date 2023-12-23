#include "main.h"

/**
 * readInput - Function reads input from user
 * Return: input
 */
char *readInput(void)
{
	char *input;
	size_t sizeOfInput;
	ssize_t charactersRead;

	input = NULL;
	sizeOfInput = 0;
	charactersRead = getline(&input, &sizeOfInput, stdin);

	if (charactersRead == -1)
	{
		free(input);
		exit(0);
	}

	return (input);
}

/**
 * inputToTokenArr - Function converts user input into an array
 * @inputStr: Input received from the user
 * Return: An array called commands
 */
char **inputToTokenArr(char *inputStr)
{
	char **commands;
	char *command;
	int i;

	commands = malloc(64);
	i = 0;

	command = strtok(inputStr, COMMANDDELIM);

	while (command != NULL)
	{
		commands[i] = strdup(command);
		i++;
		command = strtok(NULL, COMMANDDELIM);
	}
	commands[i] = NULL;

	return (commands);
}

/**
 * lookUp - Function look up the command in the path and executes if it exists
 * @tokensArr: An array of tokens
 * @env: Environment variables
 * @argv: An array of argument variables from main
 */
void lookUp(char **tokensArr, char **env, char **argv)
{
	char *pathEnv = getenv("PATH");
	char *pathToken;
	char *sPath = malloc(1024);

	if (access(tokensArr[0], F_OK) == 0)
	{

		execve(tokensArr[0], tokensArr, env);
	}
	else
	{
		pathToken = strtok(pathEnv, PATHDELIM);
		while (pathToken != NULL)
		{
			strcpy(sPath, pathToken);
			strcat(sPath, "/");
			strcat(sPath, tokensArr[0]);
			if (access(sPath, F_OK) == 0)
			{
				execve(sPath, tokensArr, env);
			}
			pathToken = strtok(NULL, PATHDELIM);
		}

		fprintf(stderr, "%s: 1: %s: not found\n", argv[0], tokensArr[0]);
		freeTokens(tokensArr);
		free(sPath);
		exit(127);
	}
}

/**
 * executeCommand - Function executes the command for the child process
 * @tokensArr: An array of tokens
 * @env: Environment variables
 * @argv: An array of argument variables from main
 */
void executeCommand(char **tokensArr, char **env, char **argv)
{
	pid_t fork_result = fork();
	int status;

	if (fork_result == 0)
	{
		lookUp(tokensArr, env, argv);
	}
	else if (fork_result < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(fork_result, &status, 0);
	}
}

/**
 * freeTokens - Function frees memory of individual tokens in token array
 * @tokensArr: An array of tokens
 */
void freeTokens(char **tokensArr)
{
	int i;

	if (tokensArr == NULL)
	{
		return;
	}

	for (i = 0; tokensArr[i] != NULL; i++)
	{
		free(tokensArr[i]);
		tokensArr[i] = NULL;
	}
	free(tokensArr);
}
