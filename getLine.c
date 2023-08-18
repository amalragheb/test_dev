#include "shell.h"

/**
 * input_buf - buffers of commands
 * @info: parameter
 * @buf: address of buffer
 * @len: address of len
 *
 * Return: readen bytes
 */
ssize_t input_buf(esh_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		r = getline(buf, &len_p, stdin);

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->flag = 1;
			remove_comments(*buf);
			*len = r;
			info->buffer = buf;
		}
	}
	return (r);
}

/**
 * read_line - gets a line
 * @info: parameter
 *
 * Return: read bytes
 */
ssize_t read_line(esh_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p, *p;

	info->arg = NULL;
	buf_p = &(info->arg);

	_putchar(FLUSH_BUFFER);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i;       /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;    /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->buffer_type = 0;
		}

		*buf_p = p;          /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r);   /* return length of buffer from _getline() */
}

/**
 * sigintHandler - blocks the  ctrl-C command
 * @sig_num: a signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
