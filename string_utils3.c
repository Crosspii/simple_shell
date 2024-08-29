#include "shell.h"

/**
 * put_char - writes a character to stdout
 * @c: The character to print
 *
 * Return: On success 1, on error -1 is returned.
 */
int put_char(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * str_ncpy - Copies a specified number of characters
 *            from one string to another.
 * @dest: The string to copy characters into.
 * @src: The string to copy characters from.
 * @num: The number of characters to copy.
 *
 * Return: The destination string.
 */
char *str_ncpy(char *dest, char *src, int num)
{
	int i, j;
	char *start = dest;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (start);
}

/**
 * str_ncat - Concatenates a specified number of characters
 *            from one string to another.
 * @dest: The string to which characters will be appended.
 * @src: The string from which characters will be taken.
 * @num: The maximum number of bytes to append.
 *
 * Return: The concatenated string.
 */
char *str_ncat(char *dest, char *src, int num)
{
	int i, j;
	char *start = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		dest[i] = '\0';
	return (start);
}

/**
 * str_chr - Finds the first occurrence of a character in a string.
 * @str: The string to search through.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of the char in the string,
 *         or NULL if the character is not found.
 */
char *str_chr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
