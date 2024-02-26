#include "shell.h"
#define MAX 1024
/**
 * main - Runs a simple shell
 * Return: Returns 0
 */

int main(void)
{
	char *lineptr, *argv[MAX], *token;
	int status, i;
	pid_t pid;
	size_t n;
	ssize_t read;

	n = 0;
	lineptr = NULL;
	while (1)
	{
		printf("($) ");
		read = getline(&lineptr, &n, stdin);
		if (read == -1)
		{
			perror("Getline ");
			return (-1);
		}
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
			continue;
		}
	}
	return (0);
}
