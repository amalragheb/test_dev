#include "shell.h"

/**
 * main - shell entry point
 * @ac: arg c
 * @av: arg v
 *
 * Return: 0 if success, 1 if error
 */
int main(__attribute__((unused)) int ac, char **av)
{
	esh_t info[] = {{ NULL, NULL, 0, NULL, NULL, NULL, 0, 0, 0, NULL, NULL, 0 }};
	ssize_t r = 0;
	int builtin_ret = 0;
	var_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;

	while (r != -1 && builtin_ret != -2)
	{
		prompt();
		r = read_line(info);
		if (r != -1)
		{
			init_esh(info, av);
			builtin_ret = check_builtin(info);
			if (builtin_ret == -1)
				execute_command(info);
		}
		free_strings(info->argv);
		info->argv = NULL;
		info->path = NULL;
	}
	reset_esh(info);
	if (!isatty(STDIN_FILENO) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (EXIT_SUCCESS);
}
