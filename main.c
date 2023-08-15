#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(__attribute__((unused)) int ac, char **av)
{
    hsh_t info[] = {INFO_INIT};
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
            init_hsh(info, av);
            builtin_ret = check_builtin(info);
            if (builtin_ret == -1)
                execute_command(info);
        }
        ffree(info->argv);
        info->argv = NULL;
        info->path = NULL;
    }
    reset_hsh(info);
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
