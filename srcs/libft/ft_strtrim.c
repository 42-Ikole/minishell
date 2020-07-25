/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 09:06:40 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/22 15:30:04 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_check(char const *s1, char const *set, int i)
{
	int j;

	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
			return (1);
		j++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i])
	{
		if (ft_check(s1, set, i))
			i++;
		else
			break ;
	}
	while (i < len)
	{
		if (ft_check(s1, set, len - 1))
			len--;
		else
			break ;
	}
	len = len - i;
	str = ft_substr(s1, i, len);
	return (str);
}
