#include "shell.h"
/**
 * is_chain:- 'Function to test if character in buffer is a chain delimiter'
 * @info: member
 * @buf: buffer member
 * @p: address of current position in buffer
 * Return: 1 || 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = j;
	return (1);
}

/**
 * check_chain:- 'Function that checks last status'
 * @info: member
 * @buf: character buffer
 * @p: current buffer position
 * @i: start ofbuffer
 * @len: length of buf
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}


/**
 * replace_alias:-'Function that replaces alias'
 * @info: member
 * Return: 1 || 0
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(info->argv[0]);
		p = strchr(node->str, '=');
		if (!p)
		{
			return (0);
		}
		p = strdup(p + 1);
		if (!p)
		{
			return (0);
		}
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars:- 'Function to replace variables in string'
 * @info: member
 * Return: 1 || 0
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			continue;
		}
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		replace_string(&info->argv[i], _strdup(" "));
	}
	return (0);
}

/**
 * replace_string:- replace string
 * @old: old string address
 * @new: new string
 * Return: 1 || 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}