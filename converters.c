#include "shell.h"

/**
 * split_str - divides a string into an array of words
 * @str: the string to be split
 * @d: the delimiters used to split the string
 *
 * Return: a pointer to an array of strings, or NULL
 */
char **split_str(char *str, char *d)
{
	char **s;
	int i, j, k, m, num_words = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * int_to_string - Converts an integer to a string representation.
 * @num: The integer to convert.
 * @base: The numerical base to use (e.g., 10 for decimal, 16 for hexadecimal).
 * @flags: Flags to modify the conversion (e.g., to handle unsigned values).
 *
 * Return: The string representation of the integer.
 */
char *int_to_string(long int num, int base, int flags)
{
	static char *digits;
	static char buf[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & TO_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	digits = flags & TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';

	do	{
		*--ptr = digits[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * str_to_int - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The converted integer if successful, 0 if no numbers are present,
 *         -1 on error (e.g., non-numeric characters in the string).
 */
int str_to_int(char *str)
{
	int i = 0;
	unsigned long int value = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			value *= 10;
			value += (str[i] - '0');
			if (value > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (value);
}
