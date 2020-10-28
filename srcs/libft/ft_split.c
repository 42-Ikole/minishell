/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 09:10:03 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/25 09:34:16 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_start(char const *s, char delim, int i, size_t len)
{
	i = i + len;
	while (s[i] == delim)
		i++;
	return (i);
}

static size_t	ft_end(char const *s, char delim, int i)
{
	size_t	len;

	len = 0;
	while (s[i] != delim && s[i])
	{
		i++;
		len++;
	}
	if (len == 0)
		len++;
	return (len);
}

static	int		ft_strcount(char const *str, char delim)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (delim == '\0' && str[i] != '\0')
		return (1);
	while (str[i])
	{
		if (str[i] != delim)
		{
			count++;
			while (str[i] != delim && str[i])
				i++;
		}
		while (str[i] == delim)
			i++;
	}
	return (count);
}

static char		**split_array(char const *s, char c, char **array, int n)
{
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	while (j < n)
	{
		i = ft_start(s, c, i, len);
		len = ft_end(s, c, i);
		array[j] = ft_substr(s, i, len);
		if (array[j] == NULL)
		{
			while (j > 0)
			{
				j--;
				free(array[j]);
			}
			free(array);
			return (NULL);
		}
		j++;
	}
	return (array);
}

char			**ft_split(char const *s, char c)
{
	char	**array;
	int		n;

	if (!s)
		return (NULL);
	n = ft_strcount(s, c);
	if (n == 0)
		n = 1;
	array = (char**)malloc((n + 1) * sizeof(char*));
	if (!array)
		return (NULL);
	array = split_array(s, c, array, n);
	if (array)
		array[n] = 0;
	return (array);
}
