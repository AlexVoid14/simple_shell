#include "shell.h"

/**
 * is_cmd:- 'Function that determines if file is executable command'
 * @info: struct member
 * @path: path to file
 * Return: 1 || 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * dup_chars:- 'Function that duplicates characters'
 * @pathstr: the path string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = 0;
	return (buf);
}

/**
 * find_path:- 'Function that finds the path string'
 * @info: member
 * @pathstr: pathe string
 * @cmd: the command to find
 * Return: full command path || NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, current_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, current_position, i);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}
