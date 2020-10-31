/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_helper.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 12:04:03 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/31 12:06:24 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h>

enum e_bool		is_exec(char *exec)
{
	char *path;

	path = NULL;
	if (!exec)
		return (false);
	if (!(ft_strncmp(exec, "cd", 3)))
		return (true);
	else if (!(ft_cmdcmp(exec, "pwd")))
		return (true);
	else if (!(ft_cmdcmp(exec, "echo")))
		return (true);
	else if (!(ft_strncmp(exec, "exit", 5)))
		return (true);
	else if (!(ft_strncmp(exec, "export", 7)))
		return (true);
	else if (!(ft_strncmp(exec, "unset", 6)))
		return (true);
	else if (!(ft_cmdcmp(exec, "env")))
		return (true);
	else if (ft_get_env("PATH", true) > 0)
		path = get_path(g_vars->envp[ft_get_env("PATH", true)][1], exec);
	if (!path)
		return (false);
	free(path);
	return (true);
}

enum e_bool		is_redirect(t_cmd *cmd, int i)
{
	while (cmd && cmd->arg && cmd->arg[i])
	{
		if (cmd->arg[i][0] <= append)
			return (true);
		i++;
	}
	return (false);
}
