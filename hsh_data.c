#include "shell.h"

/**
 * init_esh - initializes esh_t struct
 * @info: struct address
 * @av: argument av
 */
void init_esh(esh_t *info, char **av)
{
	int i = 0;

	info->esh_name = av[0];
	if (info->arg)
	{
		info->argv = _split_str(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;

		replace_vars(info);
	}
}
/**
 * reset_esh - frees esh_t struct fields
 * @info: struct address
 */
void reset_esh(esh_t *info)
{
	free_strings(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (!info->buffer)
		free(info->arg);
	if (info->env)
		free_list(&(info->env));
	free_strings(info->environ);
	info->environ = NULL;
	pfree((void **)info->buffer);
	_putchar(FLUSH_BUFFER);
}
/**
 * prompt - write prompt
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
			_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
