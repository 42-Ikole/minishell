/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:06:45 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/26 14:06:48 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h>
#include <unistd.h>

int				command_size(t_tokens *tokens)
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

t_cmd			*set_type(t_cmd *commands, char *token)
{
	if (!token)
		commands->type = semicolon;
	else if (token[0] == '|')
		commands->type = pipeline;
	else if (token[0] == ';')
		commands->type = semicolon;
	return (commands);
}

t_tokens		*free_tokens(t_tokens *tokens)
{
	t_tokens *tmp;

	while (tokens)
	{
		if (ft_ismeta(tokens->token[0]))
		{
			tmp = tokens;
			tokens = tokens->next;
			free(tmp->token);
			free(tmp);
			break ;
		}
		tmp = tokens;
		tokens = tokens->next;
		free(tmp);
	}
	return (tokens);
}

static t_cmd	*cmd_splitting(t_tokens **tk, int i)
{
	t_cmd		*commands;
	t_tokens	*tokens;

	tokens = *tk;
	commands = malloc(sizeof(t_cmd));
	malloc_check(commands);
	commands->arg = malloc(sizeof(char*) * command_size(tokens) + 1);
	malloc_check(commands->arg);
	commands->type = 0;
	while (tokens)
	{
		if (tokens->token == NULL || ft_ismeta(tokens->token[0]))
		{
			commands = set_type(commands, tokens->token);
			break ;
		}
		commands->arg[i] = tokens->token;
		tokens = tokens->next;
		i++;
	}
	*tk = free_tokens(*tk);
	commands->arg[i] = NULL;
	commands->arg = remover(commands->arg);
	return (commands);
}

t_cmd			*get_commands(t_tokens **tokens, t_cmd *commands)
{
	commands->next = cmd_splitting(tokens, 0);
	commands->read_fd = STDIN_FILENO;
	commands->write_fd = STDOUT_FILENO;
	commands = commands->next;
	commands->next = NULL;
	return (commands);
}

t_cmd			*parser(t_tokens *tokens)
{
	t_cmd		*commands;
	t_cmd		*head;

	if (!tokens->token)
	{
		free(tokens);
		return (NULL);
	}
	commands = cmd_splitting(&tokens, 0);
	head = commands;
	commands->read_fd = STDIN_FILENO;
	commands->write_fd = STDOUT_FILENO;
	commands->next = NULL;
	while (tokens)
		commands = get_commands(&tokens, commands);
	free(tokens);
	if (meta_check(head) != 0)
	{
		while (head)
			head = free_cmd(head);
		return (NULL);
	}
	return (head);
}
