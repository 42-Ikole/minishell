/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:06:18 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/26 14:06:21 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include <stdlib.h>

static int	copy_string(char **ret, char **str, int i, int length)
{
	int j;

	j = 0;
	if (length == -1)
		j++;
	while (str[i] && (length < 0 || i < length))
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	return (i);
}

static char	**split_space(char **str, int *j, int *i, int start, int k)
{
	char	**ret;
	char	**tmp;
	char	*join;
	int		size;

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
	k = copy_string(ret, str, 0, *j);
	ret[k] = ft_strjoin(join, tmp[0]);
	malloc_check(ret[k]);
	join = ft_substr(str[*j], *i, ft_strlen(str[*j]));
	malloc_check(ret[k]);
	free(str[*j]);
	size = k;
	k++;
	(*j)++;
	k = copy_string(ret, tmp, k, -1);
	ret[k - 1] = ft_strjoin(ret[k - 1], join);
	malloc_check(ret[k - 1]);
	free(join);
	free(tmp);
	while (str[*j])
	{
		ret[k] = str[*j];
		(*j)++;
		k++;
	}
	ret[k] = NULL;
	free(str);
	if ((*j) > size)
		(*j) = (*j) - size;
	else
		(*j) = size - 1;
	return (ret);
}

static char **expand_returnval(char **str, int *i, int *j, int start)
{
	char	*ret_val;

	ret_val = ft_itoa(g_vars->ret);
	malloc_check(ret_val);
	str[*j] = ft_replace_occur(str[*j], "$?", ret_val, start);
	(*i) = start + 2;
	free(ret_val);
	return (str);
}

char	**expansion_space(char **str, int *i, int *j)
{
	int		start;
	int		k;
	char	*find;

	start = *i;
	(*i)++;
	if (str[*j][*i] == '?')
		return (expand_returnval(str, i, j, start));
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
		str = split_space(str, j, i, start, k);
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
