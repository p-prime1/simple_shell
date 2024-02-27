#include "shell.h"
#define MAX 1024

/**
 * getcomm - Reads the command from the command line
 * Return: Return 0 on success and -1 on error
 */

char  *getcomm(void)
{
	char  *lineptr;
	size_t n;
	ssize_t read;

	n = 0;
	lineptr = NULL;
	read = getline(&lineptr, &n, stdin);
	if (read == -1)
	{
		perror("EOF: ");
		return (NULL);
	}
	return (lineptr);
}

/**
 * exec_comm - Executes the command
 * @argv: Argv is a Null terminated array that contains the command line args
 * Return: Return 0 on success and -1 on failure
 */

int exec_comm(char *const *argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork ");
		return (-1);
	}
	if (pid == 0)
	{
		if (access(argv[0], F_OK) != -1)
			execve(argv[0], argv, environ);
		else
		{
			perror("Command does not exist");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	return (0);
}

/**
 * main - Runs a simple shell
 * Return: Returns 0
 */

int main(void)
{
	int i, j, k;
	char *lineptr, *token, **argv;

	i = 0;
	while (1)
	{
		printf("($) ");
		lineptr = getcomm();
		argv = malloc(sizeof(char *) * (MAX + 1));
		token = strtok(lineptr, "\n");
		while (token != NULL)
		{
			argv[i] = strdup(token);
			if (argv[i] == NULL)
			{
				perror("Strdup ");
				return (-1);
			}
			token = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;
		j = exec_comm(argv);
		if (j == -1)
		{
			perror("Execve ");
			return (-1);
		}
		free(lineptr);
		argv[0] = NULL;
		for (k = 0; argv[k] != NULL; k++)
		{
			free(argv[k]);
		}
		free(argv);
		free(token);
	}
	return (0);
}
