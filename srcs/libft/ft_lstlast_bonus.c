/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 10:57:12 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/18 11:58:31 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		if (lst->next == NULL)
			return (lst);
		else
			return (ft_lstlast(lst->next));
	}
	return (NULL);
}
