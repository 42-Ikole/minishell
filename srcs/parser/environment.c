
#include "libft.h"
#include "minishell.h"
#include "stdlib.h"

void	sort_env(void)
{
    int 	i;
    int		j;
    int		k;
    char    **tmp;

    i = 0;
    while (g_vars->envp[i + 1])
    {
    	k = i + 1;
    	while (g_vars->envp[k])
		{
			j = 0;
			while (g_vars->envp[i][0][j] == g_vars->envp[k][0][j])
				j++;
			if (g_vars->envp[i][0][j] > g_vars->envp[k][0][j])
			{
				tmp = g_vars->envp[i];
				g_vars->envp[i] = g_vars->envp[k];
				g_vars->envp[k] = tmp;
			}
    		k++;
		}
        i++;
    }
}

static char **split_id(char *env)
{
	char	**split;
	int		i;

	i = 0;
	split = malloc(sizeof(char *) * 2);
	if (!split)
		errors("malloc failed");
	while (env[i] && env[i] != '=')
		i++;
	split[0] = malloc(sizeof(char) * i + 1);
	if (!split[0])
		errors("malloc failed");
	split[1] = malloc(sizeof(char) * ft_strlen(env) - i);
	if (!split[1])
		errors("malloc failed");
	ft_strlcpy(split[0], env, i + 1);
	ft_strlcpy(split[1], env + i + 1, ft_strlen(env) - i);
	return (split);
}

void	parse_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	g_vars->envp = malloc(sizeof(char **) * i + 1);
	if (!g_vars->envp)
		errors("malloc for environemt failed");
	i = 0;
	while (env[i])
	{
		g_vars->envp[i] = split_id(env[i]);
		i++;
	}
	g_vars->envp[i] = NULL;
	sort_env();
}
