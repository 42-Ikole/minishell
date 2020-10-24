/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skipmeta.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 12:59:14 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/24 15:02:55 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_skipmeta(char *str, int i)
{
	if (ft_ismeta(str[i]))
		i++;
	if (str[i] <= -2)
		i++;
	if (str[i] == -2)
		i++;
	else if (str[i] == str[i - 1])
		return (-1);
	return (i);
}
