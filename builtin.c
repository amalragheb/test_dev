#include "shell.h"

/**
 * check_builtin - search for builtin command
 * @data: the return info struct
 * Return: status number for custom builtin
 */
int check_builtin(esh_t *data)
{
	int i, return_status = -1;
	builtin_t builtins[] = {
		{"env", esh_env}, {"cd", esh_cd}, {"exit", esh_exit}, {NULL, NULL}};
	for (i = 0; builtins[i].type; i++)
		if (_strcmp(data->argv[0], builtins[i].type) == 0)
		{
			data->line_count++;
			(return_status) = builtins[i].func(data);
			break;
		}
	return (return_status);
}
/**
 * esh_exit - shell exits
 * @data: Struct containing potential arguments.
 * Return: exits with a given exit status
 */
int esh_exit(esh_t *data)
{
	int fmtcheck;

	if (data->argv[1])
		fmtcheck = _atoi(data->argv[1]);
	if (fmtcheck == -1)
		data->status = 2;
	print_error(data, "Illegal number: ");
	_puts(data->argv[1]);
	_putchar('\n');
	return (1);
	data->err_num = _atoi(data->argv[1]);
	return (-2);
	data->err_num = -1;
	return (-2);
}
