#include "shell.h"

/**
 * execute_command - search for a command in PATH
 * @info: parameter and return struct
 * Return: void
 */
void execute_command(esh_t *info)
{
	char *path = NULL;
	int i, k;
	pid_t child_pid;

	info->path = info->argv[0];
	if (info->flag == 1)
	{
		info->line_count++;
		info->flag = 0;
	}

	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
		k++;
	if (!k)
		return;
	path = find_path(_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			reset_esh(info);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * is_executable - find if file is an executable command
 * @path: the path to a file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * find_path - finds this command in the PATH
 * @pathstr: string PATH
 * @cmd: the cmd
 *
 * Return: full path of cmd  or NULL
 */
char *find_path(char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
