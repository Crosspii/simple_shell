#include "shell.h"

/**
 * main - Entry point of the shell program.
 * Return: always 0 on seccess.
 */
int main(void)
{
	char *line = NULL;
	char **args;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(EXIT_FAILURE);
		}

		line[nread - 1] = '\0';
		args = split_line(line);
		if (args[0] != NULL)
			execute(args);

		free(args);
	}

	free(line);
	return (0);
}
