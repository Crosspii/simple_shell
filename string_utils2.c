#include "shell.h"

/**
 * str_cat - appends the source string to the destination string
 * @dest: the destination string buffer
 * @src: the source string to append
 *
 * Return: pointer to the destination string buffer
 */
char *str_cat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}

/**
 * str_cpy - copies the content of one string to another
 * @dest: the buffer to copy the content to
 * @src: the string to copy from
 *
 * Return: pointer to the destination buffer
 */
char *str_cpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * str_dup - creates a new duplicate of a string
 * @str: the string to duplicate
 *
 * Return: pointer to the newly duplicated string
 */
char *str_dup(const char *str)
{
	char *result;
	int len = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--str;
	return (result);
}

/**
 * print_str - outputs a string to the standard output
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void print_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		put_char(str[i]);
		i++;
	}
}
