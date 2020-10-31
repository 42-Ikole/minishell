/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_helper.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 12:46:46 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/31 12:46:51 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

int		command_size(t_tokens *tokens)
{
	int i;

	i = 0;
	if (!tokens->token)
		return (i);
	while (tokens)
	{
		if (ft_ismeta(tokens->token[0]))
			break ;
		i++;
		tokens = tokens->next;
	}
	return (i);
}

t_cmd	*set_type(t_cmd *commands, char *token)
{
	if (!token)
		commands->type = semicolon;
	else if (token[0] == '|')
		commands->type = pipeline;
	else if (token[0] == ';')
		commands->type = semicolon;
	return (commands);
}
