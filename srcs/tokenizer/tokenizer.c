
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

t_tokens	*token_addback(t_tokens *tokens, char *token)
{
	t_tokens	*new;
	t_tokens	*head;

	if (!token)
		kut_errors("substring for token failed!\n");
	head = tokens;
	if (head->token)
	{
		new = malloc(sizeof(t_tokens));
		if (!new)
			kut_errors("yikers malloc failed!\n");
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

void		tokenizer(char *line)
{
	int i;
	int	start;
	t_tokens *tokens;
	
	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		kut_errors("malloc failed ffs\n");
	tokens->next = NULL;
	tokens->token = NULL;
	i = ft_skip_space(line, 0);
	start = i;
	while (line[i])
	{
		// printf("i = %d| start = %d| line %s\n", i, start, line);
		if ((line[i] == ' ') || !line[i + 1])
			start = fsm_space(tokens, line, start, i);
		else if (line[i] == '\"' && line[i - 1] != '\\')
			start = fsm_dq(tokens, line, start, i);
		else if (line[i] == '\'' && line[i - 1] != '\\')
			start = fsm_sq(tokens, line, start, i);
		else
			i++;
		if (start > i)
			i = start;
	}
	while (tokens)
	{
		printf("token = [%s]\n", tokens->token);
		tokens = tokens->next;
	}
}