
#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

static char **convert_env(void)
{
	char	**ret;
	int		i;

	i = 0;
	while(g_vars->envp[i])
		i++;
	ret = malloc(sizeof(char *) * i + 1);
	malloc_check(ret);
	i = 0;
	while (g_vars->envp[i])
	{
		ret[i] = ft_strdup(g_vars->envp[i][0]);
		malloc_check(ret[i]);
		ret[i] = ft_strjoin(ret[i], "=");
		malloc_check(ret[i]); 
		ret[i] = ft_strjoin(ret[i], g_vars->envp[i][1]);
		malloc_check(ret[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*get_path(char	*path, char *exec)
{
	char		**locations;
	char		*ret;
	int			i;
	struct stat	buf;

	i = 0;
	ret = NULL;
	locations = ft_split(path, ':');
	malloc_check(locations);
	while (locations[i])
	{
		locations[i] = ft_strjoin(locations[i], "/");
		malloc_check(locations[i]);
		locations[i] = ft_strjoin(locations[i], exec);
		malloc_check(locations[i]);
		stat(locations[i], &buf);
		if (S_ISREG(buf.st_mode) == true)
		{
			ret = locations[i];
			break ;
		}
		i++;
	}
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

int		exec_program(t_cmd *cmd, enum e_bool child)
{
	pid_t	pid;
	char	**env;
	char	*path;
	int		i;
	int		ret;

	pid = 0;
	ret = 0;
	path = get_path(g_vars->envp[ft_get_env("PATH")][1], cmd->arg[0]);
	if (!path && !ft_strchr(cmd->arg[0], '/'))
		return (errors("command not found", 127));
	if (child == false)
		pid = fork();
	if (pid < 0)
		exit (errors("fork failed", pid));
	else if (pid > 0)
		wait_status(pid);
	else if (pid == 0)
	{
		env = convert_env();
		if (ft_strchr(cmd->arg[0], '/'))
			ret = execve(cmd->arg[0], cmd->arg, env);
		if (ret == -1)
			exit (errors("command not found", 127));
		ret = execve(path, cmd->arg, env);
			free (path);
		i = 0;
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
		if (ret < 0)
			exit (errors("Command not found", 127));
	}
	return (0);
}

t_cmd	*select_commands(t_cmd *cmd, enum e_bool child)
{
	int	ret;
	int	backup_fd[2];

	ret = 0;
	if (!cmd || !cmd->arg || !cmd->arg[0] || !cmd->arg[0][0])
		return (cmd);
	if (is_redirect(cmd, 0))
	{
		backup_io(&backup_fd[0], &backup_fd[1]);
		ret = redirect(cmd, child);
		restore_io(backup_fd);
	}
	else if (!(ft_strncmp(cmd->arg[0], "cd", 3)))
		ret = change_dir(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "pwd")))
		ret = path_dir(cmd);
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
	g_vars->ret = ret;
	if (ret != 0 && child == false)
	{
		while (cmd)
			cmd = free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
