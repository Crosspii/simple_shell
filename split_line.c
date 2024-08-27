#include "shell.h"

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

/**
 * split_line - splits a line into multiple tokens
 * @line: the input string
 * Return: An array of tokens.
 */
char **split_line(char *line)
{
	int bufsize = TOKEN_BUFSIZE, i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += TOKEN_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
}
