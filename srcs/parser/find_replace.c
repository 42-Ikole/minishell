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

char	*ft_replace_occur(char *str, char *find, char *replace, int idx)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(str) +
		ft_strlen(replace) - ft_strlen(find) + 1));
	malloc_check(ret);
	i = 0;
	j = 0;
	k = 0;
	while ((unsigned)i < ft_strlen(str) + ft_strlen(replace) - ft_strlen(find))
	{
		if (j == idx)
		{
			while (replace[k])
			{
				ret[i] = replace[k];
				i++;
				k++;
			}
			j += ft_strlen(find);
		}
		else
		{
			ret[i] = str[j];
			i++;
			j++;
		}
	}
	ret[i] = '\0';
	free(str);
	return (ret);
}
