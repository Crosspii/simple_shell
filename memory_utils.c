#include "shell.h"

/**
 * mem_set - fills a block of memory with a specific byte value
 * @memptr: pointer to the memory area to be filled
 * @b: the byte value to fill the memory with
 * @num: the number of bytes to be filled
 *
 * Return: pointer to the memory area that was filled
 */
char *mem_set(char *memptr, char b, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		memptr[i] = b;
	return (memptr);
}

/**
 * free_ptr - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_arr - frees a dynamically allocated array of strings
 * @strsptr: pointer to the array of strings
 */
void free_arr(char **strsptr)
{
	char **temp = strsptr;

	if (!strsptr)
		return;
	while (*strsptr)
		free(*strsptr++);
	free(temp);
}

/**
 * mem_realloc - reallocates a memory block to a new size
 * @ptr: pointer to the previously allocated memory block
 * @old_size: size of the old memory block in bytes
 * @new_size: size of the new memory block in bytes
 *
 * Return: pointer to the newly allocated memory block, or NULL
 */
void *mem_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
