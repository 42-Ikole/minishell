
#include "libft.h"
#include "minishell.h"
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
	i = 0;
	while (g_vars->envp[i])
	{
		ret[i] = ft_strdup(g_vars->envp[i][0]);
		if (!ret[i])
			errors("strdup failed", 1); //
		ret[i] = ft_strjoin(ret[i], "=");
		if (!ret[i])
			errors("strjoin failed", 1); // 
		ret[i] = ft_strjoin(ret[i], g_vars->envp[i][1]);
		if (!ret[i])
			errors("ft_strjoin failed", 1); //
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
	if (!locations)
		errors("split failed", 1); //
	while (locations[i])
	{
		locations[i] = ft_strjoin(locations[i], "/");
		if (!locations[i])
			errors("ft_strjoin failed", 1); //
		locations[i] = ft_strjoin(locations[i], exec);
		if (!locations[i])
			errors("strjoin failed", 1); //
		stat(locations[i], &buf);
		if (S_ISREG(buf.st_mode) == true)
		{
			ret = locations[i];
			break ;
		}
		i++;
	}
	while (i > 0)
	{
		i--;
		free(locations[i]);
	}
	free(locations);
	return (ret);
}

int		exec_program(t_cmd *cmd)
{
	pid_t	pid;
	char	**env;
	char	*path;
	int		i;
	int		ret;

	pid = 0;
	ret = 0;
	if (cmd->type != pipeline)
	{
		pid = fork();
	}
	if (pid < 0)
		return (errors("fork failed", 1));
	else if (pid > 0)
		wait(&pid);
	else if (pid == 0 || cmd->type == pipeline)
	{
		env = convert_env();
		if (ft_strchr(cmd->arg[0], '/'))
			ret = execve(cmd->arg[0], cmd->arg, env);
		if (ret == -1)
			exit (ret);
		path = get_path(g_vars->envp[ft_get_env("PATH")][1], cmd->arg[0]);
		if (!path)
			return (errors("command not found", 1));
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
			return (errors("Command not found", 1));
		exit (ret);
	}
	return (0);
}

t_cmd	*select_commands(t_cmd *cmd)
{
	if (!cmd->arg[0])
		return (cmd);
	if (!(ft_strncmp(cmd->arg[0], "cd", 3)))
		change_dir(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "pwd")))
		path_dir(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "echo")))
		print_echo(cmd);
	else if (!(ft_strncmp(cmd->arg[0], "exit", 5)))
		ft_exit(cmd);
	else if (!(ft_strncmp(cmd->arg[0], "export", 7)))
		builtin_export(cmd);
	else if (!(ft_strncmp(cmd->arg[0], "unset", 6)))
		builtin_unset(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "env")))
		builtin_env(cmd);
	else
		exec_program(cmd);
	return (cmd);
}
