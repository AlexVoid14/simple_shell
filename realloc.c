#include "shell.h"

/**
 * *_memset:- 'Function that fills memory with constant byte'
 * @s: pointer to memory
 * @b: byte to fill
 * @n: bytes to be filled
 * Return: s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * ffree:- 'Function that frees a str of strings'
 * @pp: string of strings
 * Return: void
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
	{
		free(*pp++);
	}
	free(a);
}

/**
 * *_realloc:- 'Function to reallocate block of memory'
 * @ptr: pointer to previous malloc block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to old block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
	{
		return (malloc(sizeof(new_size)));
	}
	if (!new_size)
	{
		return (free(ptr), NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}

	p = malloc(sizeof(new_size));
	if (!p)
	{
		return (NULL);
	}

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
		p[old_size] = ((char *)ptr)[old_size];
	}
	free(ptr);
	return (p);
}
