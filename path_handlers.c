#include "shell.h"

/**
 * locate_cmd - searches for a command within the PATH directories
 * @data: pointer to the data structure
 * @pathstr: the PATH environment variable string
 * @cmd: the command to search for
 *
 * Return: the full path of the command if found, otherwise NULL
 */
char *locate_cmd(data_t *data, char *pathstr, char *cmd)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && str_starts(cmd, "./"))
	{
		if (is_exec(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, current_pos, i);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (is_exec(data, path))
				return (path);
			if (!pathstr[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * is_exec - checks if a file is an executable command
 * @data: pointer to the data structure
 * @path: path to the file to be checked
 *
 * Return: 1 if the file is executable, 0 otherwise
 */
int is_exec(data_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - copies a subset of characters from a string
 * @pathstr: the PATH environment variable string
 * @start: starting index of the substring to copy
 * @stop: ending index of the substring to copy
 *
 * Return: pointer to the copied substring buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
