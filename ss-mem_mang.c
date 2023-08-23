#include "shell.h"
/* modified */

/**
 * _memset - Sets the first n bytes of a memory area to a specified value
 * @s: A pointer to the memory area to be filled
 * @c: The value to be set
 * @n: Number of bytes to be set
 * 
 * Return: A pointer to the filled memory area
 */
char *_memset(char *s, char c, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i++] = c;
	}
	return (s);
}

/**
 * free_vector - Frees a 2D vector of strings
 * @vector: The 2D vector to free
 * 
 * Description: Iterates through the vector and frees each
 * inner string pointer. Then frees the vector pointer.
 *
 * Return: Nothing.
 */

void free_vector(char **vector)
{
	char **ptr = vector;

	if (!vector)
		return;

	while (*vector)
	{
		free(*vector++);
	}
	free(ptr);
}

/**
 * _realloc - Changes the size of the memory block pointed to by ptr
 * @ptr: Pointer to previously allocated memory
 * @old_size: Size of old block
 * @new_size: Requested size of new block
 * 
 * Return: Pointer to newly allocated memory or NULL if failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
		p[old_size] = ((char *)ptr)[old_size];
	}

	free(ptr);
	return (p);
}


/**
 * bfree - Frees memory referenced by a pointer pointer
 * @ptr: Address of pointer to free
 * 
 * Return: 1 if memory freed, 0 otherwise
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
