/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*  ft_memcpy.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 14:32:02 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/12 11:47:39 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (!((unsigned char*)dst) && (!(unsigned char*)src))
		return (NULL);
	while (i < n)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (dst);
}
