/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstew_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 09:57:02 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/18 12:00:41 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
