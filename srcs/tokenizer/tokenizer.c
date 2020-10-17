
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

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
		// printf("i = %d| start = %d| line %s\n", i, start, line + start);
		// if (line[i] == '$')
		// 	line = expansion(line, i, '\0');
		if (ft_iswhitespace(line[i]) || ft_ismeta(line[i]) || !line[i + 1])
			start = fsm_space(tokens, line, start, i);
		else if (line[i] == '\"' && ((i > 0 && line[i - 1] != '\\') || i == 0))
			start = fsm_dq(tokens, line, start, i);
		else if (line[i] == '\'' && ((i > 0 && line[i - 1] != '\\') || i == 0))
			start = fsm_sq(tokens, line, start, i);
		else
			i++;
		if (start < 0)
			return (tokens);
		if (start > i)
			i = start;
	}
	// while (tokens)
	// {
	// 	printf("token = [%s]\n", tokens->token);
	// 	tokens = tokens->next;
	// }
	return (tokens);
}
