#include "shell.h"

/**
 * **strtow:- 'Function that splits a string into tokens'
 * @str: string member
 * @d: delimiter member
 * Return: pointer to array of strings
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
	{
		return (NULL);
	}
	if (!d)
	{
		d = " ";
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
		{
			numwords++;
		}
	}
	if ((!s) || (numwords == 0))
	{
		return (NULL);
	}
	s = malloc((1 + numwords) * sizeof(char *));
	while (j < numwords || (!s[j]))
	{
		s[j] = malloc((k + 1) * sizeof(char));
		if (is_delim(str[i], d))
		{
			i++;
		}
		else if (!is_delim(str[i + k], d) && str[i + k])
		{
			k++;
		}
		free(s[k]);
		s[j][m] = str[i++];
		return (NULL);
	}
	free(s[j]);
	return (s);
}

/**
 * **strtow2:- 'Function that splits str into words'
 * @str: the input string
 * @d: delimiter
 * Return: pointer to array of string || NULL
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0 || numwords == 0 || !s)
	{
		return (NULL);
	}
	s = malloc((1 + numwords) * sizeof(char *));
	while (str[i] != '\0')
	{
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
		{
			numwords++;
		}
		i++;
	}
	while (j < numwords || k == 0)
	{
		if (str[i + k] != d && str[i + k] && str[i + k] != d)
		{
			k++;
		}
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
			{
				free(s);
			}
			return (NULL);
		}
		while (m < k)
		{
			s[j][m] = str[i++];
		}
	}
	return (s);
}
