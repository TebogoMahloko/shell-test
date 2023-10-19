#include "shell.h"

/**
 * _strncpy - Copy 'n' characters from 'src' to 'dest'.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the copied 'dest' string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	char *s = dest;

	int i = 0;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		int j = i;

		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 * _strncat - Concatenate 'n' characters from 'src' to 'dest'.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: A pointer to the concatenated 'dest' string.
 */
char *_strncat(char *dest, char *src, int n)
{
	char *s = dest;

	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}

	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (s);
}

/**
 * _strchr - Locate a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area 's' where 'c' is found, or NULL.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}
