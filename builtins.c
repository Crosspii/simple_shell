#include "shell.h"

/**
 * lookup_builtin - searches for a builtin command
 * @data: the parameter and return data structure
 *
 * Return: -1 if builtin is not found,
 *         0 if builtin executed successfully,
 *         1 if builtin was found but failed,
 *         -2 if builtin indicates exit()
 */
int lookup_builtin(data_t *data)
{
	int i, builtin_st = -1;
	builtins_t builtintbl[] = {
		{"exit", b_exit},
		{"env", b_env},
		{"help", b_help},
		{"history", b_history},
		{"setenv", b_setenv},
		{"unsetenv", b_unsetenv},
		{"cd", b_cd},
		{"alias", b_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].cmd_name; i++)
		if (str_cmp(data->args[0], builtintbl[i].cmd_name) == 0)
		{
			data->line_num++;
			builtin_st = builtintbl[i].execute(data);
			break;
		}
	return (builtin_st);
}

/**
 * b_exit - Terminates the shell session
 * @data: Structure containing command-line arguments and shell data.
 *        Used to maintain a consistent function prototype.
 * Return: Exits with a specified status code.
 *         (0) if data.args[0] != "exit"
 */
int b_exit(data_t *data)
{
	int exit_status;

	if (data->args[1])
	{
		exit_status = str_to_int(data->args[1]);
		if (exit_status == -1)
		{
			data->last_status = 2;
			print_error(data, "Illegal number: ");
			print_to_stderr(data->args[1]);
			print_char_stderr('\n');
			return (1);
		}
		data->exit_code = str_to_int(data->args[1]);
		return (-2);
	}
	data->exit_code = -1;
	return (-2);
}

/**
 * b_cd - Updates the current working directory
 * @data: Structure containing command-line arguments and shell data.
 *        Used to maintain a consistent function prototype.
 * Return: Always 0
 */
int b_cd(data_t *data)
{
	char *s, *targ_dir, buf[1024];
	int chdir_cb;

	s = getcwd(buf, 1024);
	if (!s)
		print_str("TODO: >>getcwd failure emsg here<<\n");
	if (!data->args[1])
	{
		targ_dir = env_get(data, "HOME=");
		if (!targ_dir)
			chdir_cb = /* TODO: what should this be? */
				chdir((targ_dir = env_get(data, "PWD=")) ? targ_dir : "/");
		else
			chdir_cb = chdir(targ_dir);
	}
	else if (str_cmp(data->args[1], "-") == 0)
	{
		if (!env_get(data, "OLDPWD="))
		{
			print_str(s);
			put_char('\n');
			return (1);
		}
		print_str(env_get(data, "OLDPWD=")), put_char('\n');
		chdir_cb = /* TODO: what should this be? */
			chdir((targ_dir = env_get(data, "OLDPWD=")) ? targ_dir : "/");
	}
	else
		chdir_cb = chdir(data->args[1]);
	if (chdir_cb == -1)
	{
		print_error(data, "can't cd to ");
		print_to_stderr(data->args[1]), print_char_stderr('\n');
	}
	else
	{
		env_init(data, "OLDPWD", env_get(data, "PWD="));
		env_init(data, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * b_help - Displays help information for shell commands
 * @data: Structure containing command-line arguments and shell data.
 *        Used to maintain a consistent function prototype.
 * Return: Always 0
 */
int b_help(data_t *data)
{
	char **arguments;

	arguments = data->args;
	print_str("help call works. Function not yet implemented \n");
	if (0)
		print_str(*arguments);
	return (0);
}

/**
 * b_history - Displays the command history list, showing each command
 *             on a new line, with line numbers starting at 0.
 * @data: Structure containing shell-related arguments and data.
 *        Used to maintain a consistent function prototype.
 * Return: Always 0
 */
int b_history(data_t *data)
{
	list_print(data->hist);
	return (0);
}
