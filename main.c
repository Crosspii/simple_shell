#include "shell.h"


#define BUFFER_SIZE 1024

char *find_command(char *command);

/**
 * main - Entry point of the shell program.
 * Return: always 0 on seccess.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *token;
	char *args[BUFFER_SIZE];
	int i;
	char *command_path;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("getline");
			continue;
		}

		line[nread - 1] = '\0';

		i = 0;
		token = strtok(line, " ");
		while (token != NULL && i < BUFFER_SIZE - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (args[0] != NULL)
		{
			command_path = find_command(args[0]);
			if (command_path)
			{
				args[0] = command_path;
				if (fork() == 0)
				{
					execute(args);
					exit(EXIT_FAILURE);
				}
				else
				{
					wait(NULL);
				}
				if (command_path != args[0])
					free(command_path);
			}
			else
			{
				fprintf(stderr, "%s: command not found\n",
					args[0]);
			}
		}
	}

	free(line);
	return (0);
}
