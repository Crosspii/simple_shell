#include "shell.h"

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
