#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h>

static char	**export_split(char *str)
{
	unsigned int	i;
	unsigned int	j;
	char			**ret;

	ret = malloc(sizeof(char *) * 2);
	malloc_check(ret);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ret[0] = malloc(sizeof(char) * i + 1);
	malloc_check(ret[0]);
	j = 0;
	while (j < i)
	{
		ret[0][j] = str[j];
		j++;
	}
	ret[0][j] = '\0';
	if (ft_strlen(str) - i > 0)
	{
		ret[1] = malloc(sizeof(char) * ft_strlen(str) - i + 1);
		malloc_check(str);
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
		ret[1] = ft_strdup("");
		malloc_check(ret[1]);
	}
	return (ret);
}

static int	check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '?')
			return (false);
		if (ft_isdigit(str[i]) == true)
			return (false);
		i++;
	}
	return (true);
}

static int	add_env(char **to_add)
{
	int		i;
	char	**new;
	int		size;
	char	***env;

	i = 1;
	while (to_add[i])
	{
		new = export_split(to_add[i]);
		if (check_name(new[0]) == false)
		{
			ft_putendl_fd("invalid identifier", 1);
			free(new[0]);
			free(new[1]);
			free(new);
			i++;
			continue ;
		}
		size = 0;
		while (g_vars->envp[size])
			size++;
		env = malloc(sizeof(char **) * size + 2);
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
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(g_vars->envp[i][1], 1);
			ft_putendl_fd("\"", 1);
			i++;
		}
	}
	else
		add_env(cmd->arg);
	return (0);
}
