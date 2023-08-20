#include "shell.h"

/**
 * check_builtin - search for builtin command
 * @info: the return info struct
 * Return: status number for custom builtin
 */
int check_builtin(esh_t *info)
{
	int i, return_status = -1;
	builtin_t builtins[] = {
		{"env", esh_env}, {"cd", esh_cd}, {"exit", esh_exit}, {NULL, NULL}};
	for (i = 0; builtins[i].type; i++)
		if (_strcmp(info->argv[0], builtins[i].type) == 0)
			info->line_count++;
			(return_status) = builtins[i].func(info);
			break;
	return (return_status);
}
/**
 * esh_exit - shell exits
 * @info: Struct containing potential arguments.
 * Return: exits with a given exit status
 */
int esh_exit(esh_t *info)
{
	int fmtcheck;

	if (info->argv[1])
		fmtcheck = _atoi(info->argv[1]);
		if (fmtcheck == -1)
			info->status = 2;
			print_error(info, "Illegal number: ");
			_puts(info->argv[1]);
			_putchar('\n');
			return (1);
		info->err_num = _atoi(info->argv[1]);
		return (-2);
	info->err_num = -1;
	return (-2);
}
