#include "shell.h"

/**
 * _strdup - Returns a pointer to a newly allocated space in memory
 * that has a copy of the string given as a parameter
 * @str: pointer to a string
 * Return: pointer to a new string
 */
char *_strdup(char *str)
{
	int i, l;
	char *new;

	if (!str)
	{
		return (NULL);
	}
	for (l = 0; str[l] != '\0';)
	{
		l++;
	}
	new = malloc(sizeof(char) * l + 1);
	if (!new)
	{
		return (NULL);
	}
	for (i = 0; i < l; i++)
	{
		new[i] = str[i];
	}
	new[l] = str[l];
	return (new);
}

/**
 * cancat_all - cancats all the 3 strings into a new allocated memory
 * @name: first string
 * @sep: second srting
 * @value: third string
 * Return: pointer to  the new string
 */
char *concat_all(char *name, char *sep, char *value)
{

	char *result;
	int l1, l2, l3, i, k;

	l1 = _strlen(name);
	l2 = _strlen(sep);
	l3 = _strlen(value);

	result = malloc(l1 + l2 + l3 + 1);
	if (!result)
		return (NULL);

	for (i = 0; name[i]; i++)
		result[i] = name[i];
	k = i;

	for (i = 0; sep[i]; i++)
		result[k + i] = sep[i];
	k = k + i;

	for (i = 0; value[i]; i++)
		result[k + i] = value[i];
	k = k + i;

	result[k] = '\0';

	return (result);
}

/**
 * _putchar - writes the character c to stdout
 * @c: the character to print
 * Return: On seccess 1. or on error -1 and error is set
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}


/**
 * _strlen - it gives the length of a string
 * @s: pointer to the string
 * Return: the length of srting
 */
int _strlen(char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}


/**
 * _puts - prints a string
 * @str: the pointer to string
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}
