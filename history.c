#include "shell.h"

/**
 * get_history_file:- 'Function that gets thet history file'
 * @info: struct member
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
	{
		return (NULL);
	}
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history:- Function that creates or appends a file
 * @info: member
 * Return: 1 || -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
	{
		return (-1);
	}
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, node->next);
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history:- 'Function that reads history from file'
 * @info: member
 * Return: histcount on success || 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if ((!filename) && (fd == -1) && (fsize < 2) && (!buf))
	{
		return (0);
	}
	fd = open(filename, O_RDONLY);
	free(filename);
	if (!fstat(fd, &st))
	{
		fsize = st.st_size;
	}
	buf = malloc(sizeof(char) * (fsize + 1));
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
	{
		return (free(buf), 0);
	}
	close(fd);
	while (i < fsize)
	{
		if ((buf[i] == '\n') && (last != i))
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
		free(buf);
	}
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0);
	}
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list:- 'Function that adds entry to history list'
 * @info: member
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}
	add_node_end(&node, buf, linecount);

	if (!info->history)
	{
		info->history = node;
	}
	return (0);
}

/**
 * renumber_history:- 'Function that renumbers the history list'
 * @info: member
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
