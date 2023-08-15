#include "shell.h"

/**
 * init_hsh - initializes hsh_t struct
 * @info: struct address
 * @av: argument vector
 */
void init_hsh(hsh_t *info, char **av)
{
    int i = 0;

    info->hsh_name = av[0];
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
 * free_info - frees hsh_t struct fields
 * @info: struct address
 */
void reset_hsh(hsh_t *info)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (!info->buffer)
        free(info->arg);
    if (info->env)
        free_list(&(info->env));
    ffree(info->environ);
    info->environ = NULL;
    bfree((void **)info->buffer);
    _putchar(FLUSH_BUFFER);
}
/**
 * prompt - write prompt sign string
 */
void prompt()
{
    if (isatty(STDIN_FILENO))
        _puts("$ ");
    _putchar(FLUSH_BUFFER);
}
