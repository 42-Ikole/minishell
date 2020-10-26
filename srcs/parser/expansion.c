/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:06:18 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/26 22:16:27 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h> //

static int	is_var(char c)
{
	return (c && !ft_iswhitespace(c) && c != '\"' &&
		c != '\'' && c != '$' && c != '\\');
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
	return (i);
}

static char **expand_returnval(char **str, int *i, int *j)
{
	char	*ret_val;

	ret_val = ft_itoa(g_vars->ret);
	malloc_check(ret_val);
	str[*j] = ft_replace_occur(str[*j], "$?", ret_val, (*i) - 1);
	(*i) += 3;
	free(ret_val);
	return (str);
}

static char	**expand_tokens(char **str, char *find, int *i, int *j)
{
	int		len;
	char	**tmp;
	char	**new;
	int		idx;

	(void)i;
	len = 0;
	while (str[len])
		len++;
	tmp = ft_split(g_vars->envp[ft_get_env(find)][1], ' ');
	malloc_check(tmp);
	idx = 0;
	while (tmp[idx])
		idx++;
	new = malloc(sizeof(char *) * (len + idx + 1));
	malloc_check(new);
	idx = copy_string(new, str, 0, *j);
	idx = copy_string(new, tmp, idx, -1);
	free(str[*j]);
	while (str[*j] != NULL)
	{
		(*j)++;
		new[idx] = str[*j];
		idx++;
	}
	(*j) -= len;
	return (new);
}

char	**expansion_space(char **str, int *i, int *j)
{
	char	*find;
	int		len;

	if (str[*j][(*i) + 1] == '?')
		return (expand_returnval(str, i, j));
	len = *i + 1;
	while (is_var(str[*j][len]))
		len++;
	find = ft_substr(str[*j], (*i + 1), len);
	malloc_check(find);
	str = expand_tokens(str, find, i, j);
	(*i) = 0;
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
	while (is_var(str[*i]))
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
