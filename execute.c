#include "shell.h"

#define BUFFER_SIZE 1024
/**
 * find_command - helper function to finda  command in the path
 * @command - the command to be checked if it's in the path env
 */

char *find_command(char *command)
{
	char *path_env = getenv("PATH");
	char *path = strdup(path_env);
	char *token;
	char *full_path = malloc(BUFFER_SIZE);
	int path_len;

	if (access(command, X_OK) == 0)
	{
		free(path);
		return (command);
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		path_len = strlen(token) + strlen(command) + 2;
		if (path_len > BUFFER_SIZE)
		{
			perror("Command path too long");
			free(path);
			free(full_path);
			return NULL;
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		token = strtok(NULL, ":");
	}

	free(path);
	free(full_path);
	return (NULL);
}

/**
 * execute - executes the command passed as an argument.
 * @args: an array of arguments like command and its options.
 */
void execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
