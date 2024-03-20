#include "shell.h"
/**
 * main - check code
 * @ac: arg count
 * @argv: arg vector
 * @env: environ
 *
 * Return: On success 0
 */

int main(int ac, char **argv, char **env)
{
	char *Buffer = NULL;
	size_t size_of_buff = 0;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$", 2);
		if (strcmp(argv[0], "env") == 0)
		{
			print_env(env);
			free(argv);
			continue;
		}
		if (getline(&Buffer, &size_of_buff, stdin) == -1)
		{
			free(Buffer);
			exit(EXIT_FAILURE);
		}
		Buffer[strcspn(Buffer, "\n")] = '\0';
		argv = (char **)malloc((sizeof(Buffer) + 1) * sizeof(char *));
		token(Buffer, argv);
		if (exit_comm(argv[0]))
		{
			free(argv);
			break;
		}

			exec_comm(argv);
		free(argv);
	}
	free(Buffer);

	return (0);
}


/**
 * exit_comm - exit command
 * @comm: command value
 *
 * Return: strcmp
 */

int exit_comm(char *comm)
{
	return (strcmp(comm, "exit") == 0);
}
