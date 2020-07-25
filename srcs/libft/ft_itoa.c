/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 09:12:30 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/25 10:14:57 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	int		ft_intlen(int n)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	void	ft_recursive(int n, char *dest, int len)
{
	if (n / 10 != 0)
		ft_recursive(n / 10, dest, len - 1);
	dest[len] = (n % 10 + '0');
}

char			*ft_itoa(int n)
{
	int		len;
	char	*dest;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_intlen(n);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	if (n < 0)
	{
		n = n * -1;
		dest[0] = '-';
	}
	ft_recursive(n, dest, len - 1);
	dest[len] = '\0';
	return (dest);
}
