/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:08:53 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/31 11:13:04 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

static char	**join_env(char **ret)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (g_vars->envp[i])
	{
		if (g_vars->envp[i][1])
		{
			ret[j] = ft_strdup(g_vars->envp[i][0]);
			malloc_check(ret[j]);
			ret[j] = ft_strjoin(ret[j], "=");
			malloc_check(ret[j]);
			ret[j] = ft_strjoin(ret[j], g_vars->envp[i][1]);
			malloc_check(ret[j]);
			j++;
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static char	**convert_env(void)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_vars->envp[i])
	{
		if (!g_vars->envp[i][1])
			j++;
		i++;
	}
	ret = malloc(sizeof(char *) * (i - j + 1));
	malloc_check(ret);
	ret = join_env(ret);
	return (ret);
}

char		*join_path(const char *path, const char *exec, char ***locations)
{
	struct stat	buf;
	int			i;

	i = 0;
	(*locations) = ft_split(path, ':');
	malloc_check((*locations));
	while ((*locations)[i])
	{
		(*locations)[i] = ft_strjoin((*locations)[i], "/");
		malloc_check((*locations)[i]);
		(*locations)[i] = ft_strjoin((*locations)[i], exec);
		malloc_check((*locations)[i]);
		stat((*locations)[i], &buf);
		if (S_ISREG(buf.st_mode) == true)
			return ((*locations)[i]);
		i++;
	}
	return (NULL);
}

char		*get_path(char *path, char *exec)
{
	char		**locations;
	char		*ret;
	int			i;

	ret = join_path(path, exec, &locations);
	i = 0;
	while (locations[i])
	{
		if (ft_strncmp(locations[i], ret, ft_strlen(locations[i])))
			free(locations[i]);
		i++;
	}
	free(locations);
	return (ret);
}

void		exec_child(t_cmd *cmd, char *path)
{
	char	**env;
	int		ret;
	int		i;

	ret = 0;
	env = convert_env();
	if (ft_strchr(cmd->arg[0], '/') || !path)
		ret = execve(cmd->arg[0], cmd->arg, env);
	if (ret == -1)
		exit(errors("command not found", 127));
	ret = execve(path, cmd->arg, env);
	if (path)
		free(path);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	if (ret == -1)
		exit(errors("Command not found", 127));
}

int			exec_program(t_cmd *cmd, enum e_bool child)
{
	pid_t	pid;
	char	*path;

	pid = 0;
	path = NULL;
	if (ft_get_env("PATH", true) >= 0)
		path = get_path(g_vars->envp[ft_get_env("PATH", true)][1], cmd->arg[0]);
	if (child == false)
		pid = fork();
	if (pid < 0)
		exit(errors("fork failed", pid));
	else if (pid > 0)
		wait_status(pid);
	else if (pid == 0)
		exec_child(cmd, path);
	free(path);
	return (g_vars->ret);
}

int			check_builtin(t_cmd *cmd, enum e_bool child)
{
	int ret;

	if (!(ft_strncmp(cmd->arg[0], "cd", 3)))
		ret = change_dir(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "pwd")))
		ret = path_dir();
	else if (!(ft_cmdcmp(cmd->arg[0], "echo")))
		ret = print_echo(cmd);
	else if (!(ft_strncmp(cmd->arg[0], "exit", 5)))
		ret = ft_exit(cmd, child);
	else if (!(ft_strncmp(cmd->arg[0], "export", 7)))
		ret = builtin_export(cmd);
	else if (!(ft_strncmp(cmd->arg[0], "unset", 6)))
		ret = builtin_unset(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "env")))
		ret = builtin_env(cmd);
	else
		ret = exec_program(cmd, child);
	return (ret);
}

t_cmd		*select_commands(t_cmd *cmd, enum e_bool child)
{
	int	ret;
	int	backup_fd[2];

	if (!cmd || !cmd->arg || !cmd->arg[0] || !cmd->arg[0][0])
		return (cmd);
	if (is_redirect(cmd, 0))
	{
		backup_io(&backup_fd[0], &backup_fd[1]);
		ret = redirect(cmd, child);
		restore_io(backup_fd);
	}
	else
		ret = check_builtin(cmd, child);
	g_vars->ret = ret;
	if (ret != 0)
	{
		while (cmd && cmd->type != semicolon)
			cmd = free_cmd(cmd);
		return (cmd);
	}
	return (cmd);
}
