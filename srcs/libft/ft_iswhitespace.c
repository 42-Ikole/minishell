/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iswhitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 13:06:43 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/08 11:01:30 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswhitespace(int c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}