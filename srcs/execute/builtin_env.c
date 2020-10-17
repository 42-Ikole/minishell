
#include "minishell.h"
#include "unistd.h"
#include "libft.h"

int		builtin_env(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->arg[1])
		return (errors("no arguments allowed for env", 1));
	while (g_vars->envp[i])
	{
		ft_putstr_fd(g_vars->envp[i][0], cmd->fd[1]);
		ft_putchar_fd('=', cmd->fd[1]);
		ft_putendl_fd(g_vars->envp[i][1], cmd->fd[1]);
		i++;
	}
	return (0);
}
