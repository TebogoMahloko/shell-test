#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing history file.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	return (buf);
}

/**
 * write_history - Write history to a file.
 * @info: Pointer to info_t structure.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = info->history;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history - Read history from a file and load it into the history list.
 * @info: Pointer to info_t structure.
 *
 * Return: Number of history entries read.
 */
int read_history(info_t *info)
{
	int linecount = 0;
	char *filename = get_history_file(info);

	if (!filename)
		return (0);

	int fd = open(filename, O_RDONLY);

	free(filename);

	if (fd == -1)
		return (0);

	size_t fsize = get_file_size(fd);

	if (fsize < 2)
	{
		close(fd);
		return (0);
	}

	char *buf = read_file(fd, fsize);

	close(fd);

	if (!buf)
		return (0);

	linecount = process_history_buffer(info, buf, fsize);
	free(buf);

	return (linecount);
}

/**
 * build_history_list - Adds entry to a history linked list.
 * @info: Structure containing potential arguments.
 * @buf: Buffer.
 * @linecount: The history linecount, histcount.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments.
 *
 * Return: The new histcount.
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
