
#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include <stdlib.h>

static char	**split_space_dq(char **str, int *j, int start, int k)
{
	char	**ret;
	char	**tmp;
	int		size;
	int		l;
	char	*join;

	tmp = ft_split(g_vars->envp[k][1], ' ');
	malloc_check(tmp);
	join = ft_substr(str[*j], 0, start);
	malloc_check(join);
	k = 0;
	while (tmp[k])
		k++;
	size = 0;
	while (str[size])
		size++;
	ret = malloc(sizeof(char *) * (k + size + 1));
	malloc_check(ret);
	k = 0;
	while (k < *j)
	{
		ret[k] = str[k];
		k++;
		printf("str[*j] = %s\n", str[k]);
	}
	l = 0;
	while (tmp[l])
	{
		ret[k] = tmp[l];
		l++;
		k++;
	}
	free(tmp);
	ret[k] = ft_strjoin(join, str[*j]);
	malloc_check(ret[k]);
	free(str[*j]);
	k++;
	(*j)++;
	while (str[*j])
	{
		ret[k] = str[*j];
		(*j)++;
		k++;
	}
	ret[k] = NULL;
	free(str);
	if ((*j) > l)
		(*j) = (*j) - l;
	else
		(*j) = l - 1;
	return (ret);
}

char	**expansion_dq(char **str, int *i, int *j)
{
	char	*ret_val;
	int		start;
	int		k;
	char	*find;

	start = *i;
	(*i)++;
	if (str[*j][*i] == '?')
	{
		ret_val = ft_itoa(g_vars->ret);
		malloc_check(ret_val);
		str[*j] = ft_replace_occur(str[*j], "$?", ret_val, start);
		(*i) = start + 2;
		free(ret_val);
		return (str);
	}
	while (str[*j][*i] && !ft_iswhitespace(str[*j][*i]) && str[*j][*i] != '\"' &&
		str[*j][*i] != '\'' && str[*j][*i] != '$' && str[*j][*i] != '\\')
		(*i)++;
	find = malloc(sizeof(char) * (*i) - start + 2);
	malloc_check(find);
	ft_strlcpy(find, str[*j] + start, (*i) - start + 1);
	k = 0;
	while (g_vars->envp[k] && g_vars->envp[k][0] &&
		ft_strncmp(g_vars->envp[k][0], find + 1, *i - start))
		k++;
	if (!g_vars->envp[k])
	{
		str[*j] = ft_replace_occur(str[*j], find, "", start);
		(*i) = start;
	}
	else
		str = split_space_dq(str, j, start, k);
	(*i) = 0;
	free(find);
	return (str);
}

char	*expansion(char *str, int *i)
{
	char	*ret;
	int		start;
	int		j;
	char	*find;

	start = *i;
	(*i)++;
	if (str[*i] == '?')
	{
		ret = ft_itoa(g_vars->ret);
		malloc_check(ret);
		str = ft_replace_occur(str, "$?", ret, start);
		(*i) = start + 2;
		free(ret);
		return (str);
	}
	while (str[*i] && !ft_iswhitespace(str[*i]) && str[*i] != '\"' &&
		str[*i] != '\'' && str[*i] != '$' && str[*i] != '\\')
		(*i)++;
	find = malloc(sizeof(char) * (*i) - start + 2);
	malloc_check(find);
	ft_strlcpy(find, str + start, (*i) - start + 1);
	j = 0;
	while (g_vars->envp[j] && g_vars->envp[j][0] &&
		ft_strncmp(g_vars->envp[j][0], find + 1, *i - start))
		j++;
	if (!g_vars->envp[j])
	{
		str = ft_replace_occur(str, find, "", start);
		(*i) = start;
	}
	else
	{
		str = ft_replace_occur(str, find, g_vars->envp[j][1], start);
		(*i) = start + ft_strlen(g_vars->envp[j][1]);
	}
	free(find);
	return (str);
}
