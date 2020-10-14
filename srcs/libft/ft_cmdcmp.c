/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmdcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/14 12:41:37 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/14 12:42:49 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cmdcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (!(s1[i] == s2[i] || s1[i] == ft_toupper(s2[i]) ||
			ft_toupper(s1[i]) == s2[i]))
			break ;
		i++;
	}
	if (s1[i] == s2[i] && s1[i] == '\0')
		return (0);
	else
		return (1);
}
