/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:06:37 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/26 14:06:40 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	token_check(t_cmd *cmd)
{
	int i;

	while (cmd)
	{
		i = 0;
		while (cmd->arg[i] && cmd->arg[i + 1])
		{
			if (cmd->arg[i][0] <= append && cmd->arg[i + 1][0] <= append)
				return (errors("syntax error", 258));
			i++;
		}
		if (cmd->arg[i] && cmd->arg[i][0] <= append)
			return (errors("syntax error near unexpected token newline", 258));
		cmd = cmd->next;
	}
	return (0);
}

int	meta_check(t_cmd *cmd)
{
	if (token_check(cmd))
		return (258);
	while (cmd)
	{
		if ((cmd->type == semicolon || cmd->type == pipeline) && !cmd->arg[0])
			return (errors("syntax error", 258));
		else if (cmd->type > pipeline && (!cmd->next || !cmd->next->arg[0]))
			return (errors("syntax error near unexpected token newline", 258));
		else if (cmd->next && cmd->type == cmd->next->type &&
			!cmd->next->arg[0])
			return (errors("syntax error", 258));
		else if (cmd->type == pipeline && !cmd->next &&
			cmd->next->type < pipeline)
			return (errors("syntax error", 258));
		cmd = cmd->next;
	}
	return (0);
}
