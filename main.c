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
    info_t info[] = {INFO_INIT};
    ssize_t r = 0;
    int builtin_ret = 0;

    populate_env_list(info);

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (isatty(STDIN_FILENO))
            _puts("$ ");
        _putchar(FLUSH_BUFFER);
        r = get_input(info);
        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_cmd(info);
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
