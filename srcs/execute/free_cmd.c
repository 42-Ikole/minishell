/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:08:23 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/26 14:08:25 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdlib.h"

t_cmd	*free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*next;

	i = 0;
	while (cmd->arg[i])
	{
		free(cmd->arg[i]);
		i++;
	}
	free(cmd->arg);
	next = cmd->next;
	free(cmd);
	return (next);
}
