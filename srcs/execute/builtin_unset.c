/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:20:35 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/26 14:20:37 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

static void	unset_elm(int size, int index)
{
	int		i;
	char	***tmp;

	tmp = malloc(sizeof(char **) * size);
	malloc_check(tmp);
	i = 0;
	while (size > i)
	{
		if (i >= index)
			tmp[i] = g_vars->envp[i + 1];
		else
			tmp[i] = g_vars->envp[i];
		i++;
	}
	free(g_vars->envp);
	g_vars->envp = tmp;
	g_vars->ret = 0;
}

int			builtin_unset(t_cmd *cmd)
{
	int	i;
	int index;
	int size;

	i = 1;
	g_vars->ret = 0;
	while (cmd->arg[i])
	{
		if (check_name(cmd->arg[i]) == false)
			errors("Not a valid identifier", 1);
		index = ft_get_env(cmd->arg[i]);
		if (index >= 0)
		{
			size = 0;
			while (g_vars->envp[size])
				size++;
			free(g_vars->envp[index][0]);
			if (g_vars->envp[index][1])
				free(g_vars->envp[index][1]);
			free(g_vars->envp[index]);
			unset_elm(size, index);
		}
		i++;
	}
	return (g_vars->ret);
}
