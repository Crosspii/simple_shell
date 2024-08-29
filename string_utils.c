#include "shell.h"

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * str_len - calculates the number of characters in a string
 * @str: the input string to evaluate
 *
 * Return: the count of characters in the string as an integer
 */
int str_len(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * str_cmp - compares two strings lexicographically
 * @str1: the first string to compare
 * @str2: the second string to compare
 *
 * Return: -1 if str1 < str2, 1 if str1 > str2, 0 if equal
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * str_starts - determines if one string begins with another
 * @haystack: the string to search within
 * @prefix: the substring to check for at the beginning
 *
 * Return: pointer to the next character in main_str or NULL
 */
char *str_starts(const char *haystack, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
