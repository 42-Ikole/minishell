
#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <limits.h>

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
		ret[i] = ft_strjoin(ret[i], "=");
		ret[i] = ft_strjoin(ret[i], g_vars->envp[i][1]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	exec_program(t_cmd *cmd)
{
	pid_t	pid;
	char	**env;
	int		i;
	int		ret;

	pid = 0;
	if (cmd->type != pipeline)
	{
		pid = fork();
		if (pid < 0)
			errors("fork failed");
		else if (pid > 0)
			wait(&pid);
	}
	if (pid == 0 || cmd->type == pipeline)
	{
		env = convert_env();
		// printf("%s\n", env[ft_get_env("PATH")]);
		ret = execve("/bin/ls", cmd->arg, env);
		i = 0;
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
		if (ret < 0)
			errors("Command not found");
		exit (ret);
	}
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
