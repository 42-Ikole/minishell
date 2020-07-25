/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:46:15 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/19 15:01:12 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!dst || !src)
		return (0);
	while (src[j] != '\0')
	{
		if (i < dstsize - 1 && dstsize > 0)
		{
			dst[i] = src[i];
			i++;
		}
		j++;
	}
	if (dstsize == 0)
		return (j);
	dst[i] = '\0';
	return (j);
}
