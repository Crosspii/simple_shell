#include "shell.h"

/**
 * hsh - primary loop for the shell execution
 * @data: the parameter and return data structure
 * @av: the argument vector from the main function
 *
 * Return: 0 on success, 1 on error, or specific error code
 */
int hsh(data_t *data, char **av)
{
	int built_in_ret = 0;
	ssize_t r = 0;

	while (r != -1 && built_in_ret != -2)
	{
		clear_data(data);
		if (isatty(STDIN_FILENO) && data->input_fd <= 2)
			print_str("$ ");
		print_char_stderr(BUF_FLUSH);
		r = input_get_line(data);
		if (r != -1)
		{
			set_data(data, av);
			built_in_ret = lookup_builtin(data);
			if (built_in_ret == -1)
				search_cmd(data);
		}
		else if (isatty(STDIN_FILENO) && data->input_fd <= 2)
			put_char('\n');
		free_data(data, 0);
	}
	hist_create(data);
	free_data(data, 1);
	if (!(isatty(STDIN_FILENO) && data->input_fd <= 2) && data->last_status)
		exit(data->last_status);
	if (built_in_ret == -2)
	{
		if (data->exit_code == -1)
			exit(data->last_status);
		exit(data->exit_code);
	}
	return (built_in_ret);
}

/**
 * search_cmd - searches for a command in the PATH environment variable
 * @data: the parameter and return data structure
 *
 * Return: void
 */
void search_cmd(data_t *data)
{
	char *path = NULL;
	int i, char_count;

	data->exec_path = data->args[0];
	if (data->line_flag == 1)
	{
		data->line_num++;
		data->line_flag = 0;
	}
	for (i = 0, char_count = 0; data->input[i]; i++)
		if (!is_delim(data->input[i], " \t\n"))
			char_count++;
	if (!char_count)
		return;

	path = locate_cmd(data, env_get(data, "PATH="), data->args[0]);
	if (path)
	{
		data->exec_path = path;
		fork_and_exec(data);
	}
	else
	{
		if (((isatty(STDIN_FILENO) && data->input_fd <= 2) || env_get(data, "PATH=")
			|| data->args[0][0] == '/') && is_exec(data, data->args[0]))
			fork_and_exec(data);
		else if (*(data->input) != '\n')
		{
			data->last_status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * fork_and_exec - forks a process and executes the command
 * @data: the parameter and return data structure
 *
 * Return: void
 */
void fork_and_exec(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->exec_path, data->args, env_to_arr(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->last_status));
		if (WIFEXITED(data->last_status))
		{
			data->last_status = WEXITSTATUS(data->last_status);
			if (data->last_status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
