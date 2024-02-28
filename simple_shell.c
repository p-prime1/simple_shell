#include "shell.h"
#define MAX 1024

void print_env(void)
{
    char **env;
    int i;

    env = environ;
    i = 0;
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
}
/**
 * build_path - Builds the path
 * @argv: Pointer to argv
 * Return: Returns the built path on success or NULL on error
 */

char *build_path(char ***argv)
{
	char *temp_env;
	char *token;
	char *path;

	temp_env = strdup(getenv("PATH"));
	if (temp_env != NULL)
	{
		token = strtok(temp_env, ":");
		while (token != NULL)
		{
			path = malloc(strlen(token) + strlen(*argv[0]) + 2);
			strcpy(path, token);
			strcat(path, "/");
			strcat(path, *argv[0]);
			if (access(path, F_OK) == 0)
			{
				free(temp_env);
				return (path);
			}
			else
			{
				token = strtok(NULL, ":");
				free(path);
			}
		}
	}
	free(temp_env);
	return (NULL);
}
/**
 * getcomm - Reads the command from the command line
 * Return: Return 0 on success and -1 on error
 */

char  **getcomm(void)
{
	char  *lineptr, *token, **argv;
	size_t n, i;
	ssize_t read;

	n = 0;
	i = 0;
	lineptr = NULL;
	read = getline(&lineptr, &n, stdin);
	if (read == -1)
	{
		perror("EOF: ");
		return (NULL);
	}
	argv = malloc(sizeof(char *) * (MAX + 1));
	token = strtok(lineptr, "\n");
	while (token != NULL)
	{
		argv[i] = strdup(token);
		if (argv[i] == NULL)
		{
			perror("Strdup ");
			return (NULL);
		}
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * exec_comm - Executes the command
 * @argv: Argv is a Null terminated array that contains the command line args
 * Return: Return 0 on success and -1 on failure
 */

int exec_comm(char **argv)
{
	pid_t pid;
	int status;
	char *a;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork ");
		return (-1);
	}
	if (pid == 0)
	{
		if (argv[0][0] != '/')
		{
			a = build_path(&argv);
			if (a == NULL)
			{
				perror("Command doent exist ");
				exit(EXIT_FAILURE);
			}
		}
		else
			a = strdup(argv[0]);
		if (strcmp(a, "env") == 0)
		{
			print_env();
			return (0);
		}
		if (execve(a, argv, environ) == -1)
		{
			perror("Execve ");
			return (-1);
		}
		free(a);
	}
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
	int k;
	char **argv;

	while (1)
	{
		printf("($) ");
		argv = getcomm();
		if (strcmp(argv[0], "exit") == 0)
			_exit(0);
		else
		{
			exec_comm(argv);
		}
		argv[0] = NULL;
		for (k = 0; argv[k] != NULL; k++)
		{
			free(argv[k]);
		}
		free(argv);
	}
	return (0);
}
