/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/24 10:33:11 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/24 16:06:19 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h>

static void		*free_tokens(t_tokens *tokens)
{
	t_tokens *tmp;

	while (tokens)
	{
		tmp = tokens;
		free(tokens->token);
		tokens = tokens->next;
		free(tmp);
	}
	return (NULL);
}

t_tokens		*token_addback(t_tokens *tokens, char *token)
{
	t_tokens	*new;
	t_tokens	*head;

	malloc_check(tokens);
	head = tokens;
	if (head->token)
	{
		new = malloc(sizeof(t_tokens));
		malloc_check(new);
		new->token = token;
		new->next = NULL;
		while (tokens && tokens->next)
			tokens = tokens->next;
		if (tokens)
			tokens->next = new;
		else
			head = new;
	}
	else
		head->token = token;
	return (head);
}

static void		choose_state(char *line, t_tokens *tokens, int *i, int *start)
{
	if (ft_iswhitespace(line[(*i)]) || ft_ismeta(line[(*i)]) ||
		!line[(*i) + 1] || line[(*i)] <= append)
		(*start) = fsm_space(tokens, line, (*start), (*i));
	else if (line[(*i)] == '\"' && (((*i) > 0 && line[(*i) - 1] != '\\')
		|| (*i) == 0))
		(*start) = fsm_dq(tokens, line, (*start), (*i));
	else if (line[(*i)] == '\'' && (((*i) > 0 && line[(*i) - 1] != '\\')
		|| (*i) == 0))
		(*start) = fsm_sq(tokens, line, (*start), (*i));
	else
		(*i)++;
}

t_tokens		*tokenizer(char *line)
{
	int			i;
	int			start;
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	malloc_check(tokens);
	tokens->next = NULL;
	tokens->token = NULL;
	i = ft_skip_space(line, 0);
	start = i;
	while (line[i])
	{
		if (format_de(line, i))
			return (free_tokens(tokens));
		format_redirect(line, i);
		if (line[i] == '\\' && ft_iswhitespace(line[i + 1]))
			i += 2;
		choose_state(line, tokens, &i, &start);
		if (start == -1)
			return (free_tokens(tokens));
		if (start > i)
			i = start;
	}
	return (tokens);
}
