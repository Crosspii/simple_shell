#include "shell.h"

/**
 * print_to_stderr - Outputs a string to standard error (stderr).
 * @str: The string to be printed.
 *
 * Return: Nothing
 */
void print_to_stderr(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		print_char_stderr(str[index]);
		index++;
	}
}

/**
 * print_char_stderr - Writes a single character to standard error (stderr).
 * @c: The character to print.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int print_char_stderr(char c)
{
	static int buf_index;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= BUF_SIZE)
	{
		write(2, buf, buf_index);
		buf_index = 0;
	}
	if (c != BUF_FLUSH)
		buf[buf_index++] = c;
	return (1);
}

/**
 * print_error - Prints an error message to standard error (stderr).
 * @data: The structure containing the parameter and return data.
 * @errstr: The error message to be printed.
 *
 * Return: Nothing.
 */
void print_error(data_t *data, char *errstr)
{
	print_to_stderr(data->file_name);
	print_to_stderr(": ");
	print_int(data->line_num, STDERR_FILENO);
	print_to_stderr(": ");
	print_to_stderr(data->args[0]);
	print_to_stderr(": ");
	print_to_stderr(errstr);
}

/**
 * print_int - Prints an integer in decimal (base 10) format.
 * @num: The integer to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_int(int num, int fd)
{
	int (*output_char)(char) = put_char;
	int i, count = 0;
	unsigned int abs_value, curr;

	if (fd == STDERR_FILENO)
		output_char = print_char_stderr;
	if (num < 0)
	{
		abs_value = -num;
		output_char('-');
		count++;
	}
	else
		abs_value = num;
	curr = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			output_char('0' + curr / i);
			count++;
		}
		curr %= i;
	}
	output_char('0' + curr);
	count++;

	return (count);
}

/**
 * print_file_error - Prints an error message when a file cannot be opened.
 * @av: The argument vector from main.
 *
 * Return: Nothing.
 */
void print_file_error(char **av)
{
	print_to_stderr(av[0]);
	print_to_stderr(": 0: Can't open ");
	print_to_stderr(av[1]);
	print_char_stderr('\n');
	print_char_stderr(BUF_FLUSH);
}
