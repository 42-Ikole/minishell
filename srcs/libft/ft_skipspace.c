/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skipspace.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 16:45:53 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/06 13:29:04 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_skip_space(char *line, int i)
{
	while (ft_iswhitespace(line[i]))
		i++;
	return (i);
}
