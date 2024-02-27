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
		perror("Getline ");
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
		execve(argv[0], argv, environ);
	else
	{
		wait(&status);
	}
	return (0);

}

/**
 * main - Runs a simple shell
 * Return: Returns 0
 */

int main(void)
{
	int i, j;
	char *lineptr, *token, *argv[MAX];

	while (1)
	{
		printf("($) ");
		lineptr = getcomm();
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
			continue;
		}
	}
	free(lineptr);
	free(argv);
	free(token);
	return (0);
}
