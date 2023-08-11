#include "shell.h"

void set_info(info_t *info, char **av);

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(__attribute__((unused)) int ac, char **av)
{
    info_t info[] = {INFO_INIT};
    ssize_t r = 0;
    int builtin_ret = 0;
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;

    while (r != -1 && builtin_ret != -2)
    {
        if (isatty(STDIN_FILENO))
            _puts("$ ");
        _putchar(FLUSH_BUFFER);
        r = get_input(info);
        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                execute_command(info);
        }
        free_info(info, 0);
    }
    free_info(info, 1);
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

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
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
