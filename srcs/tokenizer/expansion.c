
#include "libft.h"
#include "minishell.h"
#include "stdlib.h"

char	*expansion(char *str, int *i)
{
	char	*ret;
	int		start;
	int		j;
	char	*find;

	start = *i;
	ret = ft_itoa(g_vars->ret);
	if (!ret)
		errors("malloc failed");
	(*i)++;
	if (str[*i] == '?')
	{
		str = ft_replace_occur(str, "$?", ret, ft_strlen(str) + (ft_strlen(ret) - 2));
		free(ret);
		return (str);
	}
	while (str[*i] && !ft_iswhitespace(str[*i]) && str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
	find = malloc(sizeof(char) * *i - start + 2);
	if (!find)
		errors("malloc failed");
	ft_strlcpy(find, str + start, *i - start + 1);
	j = 0;
	while (g_vars->envp[j] && g_vars->envp[j][0] && ft_strncmp(g_vars->envp[j][0], find + 1, *i - start))
		j++;
	if (!g_vars->envp[j])
		str = ft_replace_occur(str, find, "", ft_strlen(str) - ft_strlen(find));
	else
		str = ft_replace_occur(str, find, g_vars->envp[j][1],
			ft_strlen(str) + ft_strlen(g_vars->envp[j][1]) - ft_strlen(find));
	free (find);
	return (str);	
}
