/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_helper.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 11:56:00 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/31 12:02:13 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include <unistd.h>
#include <sys/stat.h>

char	**join_env(char **ret)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (g_vars->envp[i])
	{
		if (g_vars->envp[i][1])
		{
			ret[j] = ft_strdup(g_vars->envp[i][0]);
			malloc_check(ret[j]);
			ret[j] = ft_strjoin(ret[j], "=");
			malloc_check(ret[j]);
			ret[j] = ft_strjoin(ret[j], g_vars->envp[i][1]);
			malloc_check(ret[j]);
			j++;
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**convert_env(void)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_vars->envp[i])
	{
		if (!g_vars->envp[i][1])
			j++;
		i++;
	}
	ret = malloc(sizeof(char *) * (i - j + 1));
	malloc_check(ret);
	ret = join_env(ret);
	return (ret);
}

char	*join_path(const char *path, const char *exec, char ***locations)
{
	struct stat	buf;
	int			i;

	i = 0;
	(*locations) = ft_split(path, ':');
	malloc_check((*locations));
	while ((*locations)[i])
	{
		(*locations)[i] = ft_strjoin((*locations)[i], "/");
		malloc_check((*locations)[i]);
		(*locations)[i] = ft_strjoin((*locations)[i], exec);
		malloc_check((*locations)[i]);
		stat((*locations)[i], &buf);
		if (S_ISREG(buf.st_mode) == true)
			return ((*locations)[i]);
		i++;
	}
	return (NULL);
}
