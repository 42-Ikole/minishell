/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_helper.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 12:53:57 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/11/01 12:12:53 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include <stdlib.h>

int		is_escapable(char c)
{
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9')))
		return (false);
	return (true);
}

int		is_var(char *str, int i)
{
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
		return (i);
	i++;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char	*ft_tokenjoin(char *s1, char *s2)
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

int		copy_string(char **ret, char **str, int i, int length)
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

char	**expand_returnval(char **str, int *i, int *j)
{
	char	*ret_val;

	ret_val = ft_itoa(g_vars->ret);
	malloc_check(ret_val);
	str[*j] = ft_replace_occur(str[*j], "$?", ret_val, (*i));
	(*i) += ft_strlen(ret_val);
	free(ret_val);
	return (str);
}
