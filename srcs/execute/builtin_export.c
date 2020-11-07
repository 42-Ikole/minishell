/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:20:44 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/11/07 13:26:44 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h>

char		**get_string(char *str, unsigned int i, unsigned int j, char **ret)
{
	if (ft_strlen(str) - i > 0)
	{
		ret[1] = malloc(sizeof(char) * ft_strlen(str) - i + 1);
		malloc_check(ret[1]);
		i = j + 1;
		j = 0;
		while (str[i])
		{
			ret[1][j] = str[i];
			i++;
			j++;
		}
		ret[1][j] = '\0';
	}
	else
	{
		if (str[i] == '=')
		{
			ret[1] = ft_strdup("");
			malloc_check(ret[1]);
		}
		else
			ret[1] = NULL;
	}
	return (ret);
}

static char	**export_split(char *str)
{
	unsigned int	i;
	char			**ret;

	ret = malloc(sizeof(char *) * 2);
	malloc_check(ret);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ret[0] = ft_substr(str, 0, i);
	ret = get_string(str, i, i, ret);
	i = 0;
	if (ret[1])
		ret[1] = multiply_escape(ret[1]);
	return (ret);
}

static int	add_env(char **to_add)
{
	int		i;
	char	**new;

	i = 1;
	while (to_add[i])
	{
		new = export_split(to_add[i]);
		if (check_name(new[0]) == false)
		{
			errors("Not a valid identifier", 1);
			free(new[0]);
			free(new[1]);
			free(new);
		}
		else if (ft_get_env(new[0], false) >= 0)
			replace_env(new);
		else
			copy_env(new);
		i++;
	}
	sort_env();
	return (0);
}

int			builtin_export(t_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd->arg[1])
	{
		while (g_vars->envp[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(g_vars->envp[i][0], 1);
			if (g_vars->envp[i][1])
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(g_vars->envp[i][1], 1);
				ft_putchar_fd('\"', 1);
			}
			ft_putchar_fd('\n', 1);
			i++;
		}
		g_vars->ret = 0;
	}
	else
		add_env(cmd->arg);
	return (g_vars->ret);
}
