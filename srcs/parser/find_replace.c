/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_replace.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:06:28 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/26 14:21:53 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"

int			replace_it(char *replace, int i, char *ret)
{
	int k;

	k = 0;
	while (replace[k])
	{
		ret[i] = replace[k];
		i++;
		k++;
	}
	return (i);
}

static void	regular_copy(char *str, char *ret, int *i, int *j)
{
	ret[(*i)] = str[(*j)];
	(*i)++;
	(*j)++;
}

char		*ft_replace_occur(char *str, char *find, char *replace, int idx)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(str) +
		ft_strlen(replace) - ft_strlen(find) + 1));
	malloc_check(ret);
	i = 0;
	j = 0;
	while ((unsigned)i < ft_strlen(str) + ft_strlen(replace) - ft_strlen(find))
	{
		if (j == idx)
		{
			i = replace_it(replace, i, ret);
			j += ft_strlen(find);
		}
		else
			regular_copy(str, ret, &i, &j);
	}
	ret[i] = '\0';
	free(str);
	return (ret);
}
