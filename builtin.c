#include "shell.h"

/**
 * check_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int check_builtin(esh_t *info)
{
    int i, return_status = -1;
    builtin_t builtins[] = {
        {"env", esh_env},
        {"cd", esh_cd},
        {"exit", esh_exit},
        {NULL, NULL}};

    for (i = 0; builtins[i].type; i++)
        if (_strcmp(info->argv[0], builtins[i].type) == 0)
        {
            info->line_count++;
            return_status = builtins[i].func(info);
            break;
        }
    return (return_status);
}

/**
 * esh_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int esh_exit(esh_t *info)
{
    int fmtcheck;

    if (info->argv[1]) /* If there is an exit arguement */
    {
        fmtcheck = _atoi(info->argv[1]);
        if (fmtcheck == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _puts(info->argv[1]);
            _putchar('\n');
            return (1);
        }
        info->err_num = _atoi(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * esh_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int esh_cd(esh_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("getcwd failure\n");
    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _puts(info->argv[1]), _putchar('\n');
    }

    return (0);
}
