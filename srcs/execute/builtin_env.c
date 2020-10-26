/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:20:49 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/26 14:20:51 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include "libft.h"

int		builtin_env(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->arg[1])
		return (errors("no arguments allowed for env", 127));
	while (g_vars->envp[i])
	{
		if (g_vars->envp[i][1])
		{
			ft_putstr_fd(g_vars->envp[i][0], 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(g_vars->envp[i][1], 1);
		}
		i++;
	}
	return (0);
}
