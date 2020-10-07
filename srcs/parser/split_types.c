/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_types.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 14:22:11 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/07 12:55:42 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_cmd	*split_semicolon(t_tokens *tokens)
{
	enum state current;
	char *argument;
	t_tokens *head;
	int i;

	current = space;
	argument = ft_strdup("");
	head = tokens;
	if (!argument)
		kut_errors("ooops looks like strdup failed :(");
	while (tokens->next)
	{
		if (tokens->token == NULL)
			return ;
		i = 0;
		while (tokens->token[i])
		{
			if (tokens->token[i] == ';' && current == space)
				return ; // doe iets ofzo
		}
	}	
}
