/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:06:18 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/31 08:51:34 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include <stdlib.h>

static int	is_var(char *str, int i)
{
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' &&
		str[i] <= 'Z') || str[i] == '_'))
		return (i);
	i++;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

static char	*ft_tokenjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	free(s2);
	return (str);
}

static int	copy_string(char **ret, char **str, int i, int length)
{
	int j;

	j = 0;
	while (str[j] && (length < 0 || i < length))
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	if (length >= 0)
		free(str[j]);
	return (i);
}

static char	**expand_returnval(char **str, int *i, int *j)
{
	char	*ret_val;

	ret_val = ft_itoa(g_vars->ret);
	malloc_check(ret_val);
	str[*j] = ft_replace_occur(str[*j], "$?", ret_val, (*i));
	(*i) += ft_strlen(ret_val);
	free(ret_val);
	return (str);
}

static char	**get_split(char **str, char *find, int *i, int *j)
{
	char	**tmp;
	int		idx;

	tmp = ft_split(g_vars->envp[ft_get_env(find, true)][1], ' ');
	malloc_check(tmp);
	idx = 0;
	tmp[idx] = ft_tokenjoin(ft_substr(str[*j], idx, *i), tmp[idx]);
	malloc_check(tmp[idx]);
	while (tmp[idx + 1])
		idx++;
	tmp[idx] = ft_tokenjoin(tmp[idx],
		ft_substr(str[*j], (*i) + ft_strlen(find) + 1, -1));
	malloc_check(tmp[idx]);
	return (tmp);
}

static char	**expand_tokens(char **str, char *find, int *i, int *j)
{
	int		len;
	char	**tmp;
	char	**new;
	int		idx;

	len = 0;
	while (str[len])
		len++;
	tmp = get_split(str, find, i, j);
	idx = 0;
	while (tmp[idx])
		idx++;
	new = malloc(sizeof(char *) * (len + idx + 1));
	malloc_check(new);
	idx = copy_string(new, str, 0, *j);
	idx = copy_string(new, tmp, idx, -1);
	while (str[*j] != NULL)
	{
		(*j)++;
		new[idx] = str[*j];
		idx++;
	}
	free(str);
	free(tmp);
	return (new);
}

char		**expansion_space(char **str, int *i, int *j)
{
	char	*find;
	int		len;

	if (!str[*j][(*i) + 1])
	{
		(*i)++;
		return (str);
	}
	if (str[*j][(*i) + 1] == '?')
		return (expand_returnval(str, i, j));
	len = is_var(str[*j], (*i) + 1);
	find = ft_substr(str[*j], *i, len - *i);
	malloc_check(find);
	if (ft_get_env(find + 1, true) < 0)
		str[*j] = ft_replace_occur(str[*j], find, "", (*i));
	else
	{
		str = expand_tokens(str, find + 1, i, j);
		(*j) = 0;
		(*i) = 0;
	}
	free(find);
	return (str);
}

static char	*expand_string(char *str, int *i, int start)
{
	int		j;
	char	*find;

	(*i) = is_var(str, *i);
	find = malloc(sizeof(char) * (*i) - start + 2);
	malloc_check(find);
	ft_strlcpy(find, str + start, (*i) - start + 1);
	j = 0;
	while (g_vars->envp[j] && g_vars->envp[j][0] &&
		ft_strncmp(g_vars->envp[j][0], find + 1, *i - start))
		j++;
	if (!g_vars->envp[j] || !g_vars->envp[j][1])
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

char		*expansion(char *str, int *i)
{
	char	*ret;
	int		start;

	start = *i;
	(*i)++;
	if (!str[*i])
		return (str);
	if (str[*i] == '?')
	{
		ret = ft_itoa(g_vars->ret);
		malloc_check(ret);
		str = ft_replace_occur(str, "$?", ret, start);
		(*i) = start + ft_strlen(ret);
		free(ret);
		return (str);
	}
	return (expand_string(str, i, start));
}
