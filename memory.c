#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @pto: address of the pointer to free
 *
 * Return: 1 if freed and checked for errors, otherwise 0.
 */
int bfree(void **pto)
{
	if (pto != NULL && *pto != NULL)
	{
		free(*pto);
		if (*pto == NULL)
		{
			return (1);
		}
	}
	return (0);
}
