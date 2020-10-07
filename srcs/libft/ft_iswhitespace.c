/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iswhitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 13:06:43 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/06 14:04:50 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define TRUE 1
#define FALSE 0

int	ft_iswhitespace(int c)
{
	if (c == '\t' || c == ' ')
		return (TRUE);
	return (FALSE);
}
