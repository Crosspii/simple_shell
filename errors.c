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
 * rm_comments - Removes comments from a string by replacing the first
 *               instance of '#' with a null terminator ('\0').
 * @buf: The string to modify.
 *
 * Return: Always 0.
 */
void rm_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * write_char_fd - Writes a single character to the specified file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int write_char_fd(char c, int fd)
{
	static int buf_index;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= BUF_SIZE)
	{
		write(fd, buf, buf_index);
		buf_index = 0;
	}
	if (c != BUF_FLUSH)
		buf[buf_index++] = c;
	return (1);
}

/**
 * write_str_fd - Outputs a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int write_str_fd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		char_count += write_char_fd(*str++, fd);
	}
	return (char_count);
}
