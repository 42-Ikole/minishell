/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 09:43:29 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/19 14:36:32 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*locate;
	size_t	i;
	size_t	len;

	i = 0;
	len = count * size;
	locate = malloc(len);
	if (!locate)
		return (NULL);
	while (i < len)
	{
		((unsigned char*)locate)[i] = 0;
		i++;
	}
	return (locate);
}
