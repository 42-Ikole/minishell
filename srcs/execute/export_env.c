/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 11:49:49 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/31 11:51:14 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h>

int		check_name(char *str)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' &&
		str[i] <= 'Z') || str[i] == '_'))
		return (false);
	i++;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i])
		return (false);
	return (true);
}

void	copy_env(char **new)
{
	int		size;
	char	***env;

	size = 0;
	while (g_vars->envp[size])
		size++;
	env = malloc(sizeof(char **) * (size + 2));
	malloc_check(env);
	size = 0;
	while (g_vars->envp[size])
	{
		env[size] = g_vars->envp[size];
		size++;
	}
	env[size] = new;
	env[size + 1] = NULL;
	free(g_vars->envp);
	g_vars->envp = env;
}

void	replace_env(char **new)
{
	if (new[1])
	{
		if (g_vars->envp[ft_get_env(new[0], false)][1])
			free(g_vars->envp[ft_get_env(new[0], false)][1]);
		g_vars->envp[ft_get_env(new[0], false)][1] = new[1];
	}
	else
		free(new[1]);
	free(new[0]);
	free(new);
}
