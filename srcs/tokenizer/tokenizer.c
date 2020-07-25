
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_tokens	*token_addback(t_tokens *tokens, char *token, int length)
{
	t_tokens	*new;
	t_tokens	*head;

	head = tokens;
	// printf("tkad = %s\n", token);
	new = malloc(sizeof(t_tokens));
	if (!new)
		kut_errors("yikers malloc failed!\n");
	new->token = ft_substr(token, 0, length);
	// printf("sub = %s\n", new->token);
	if (!new->token)
		kut_errors("substring for token failed");
	new->next = NULL;
	while (tokens && tokens->next)
		tokens = tokens->next;
	if (tokens)
		tokens->next = new;
	else
		head = new;
	return (head);
}

void		tokenizer(char *line)
{
	int i;
	int j;
	t_tokens *tokens;

	
	tokens = NULL;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i + 1] == '\0') //pakt laatste char van string niet
		{
			tokens = token_addback(tokens, line + j, i - j);
			while (line[i] == ' ')
				i++;
			j = i;
		}
		i++;
	}
	// printf("tk = %s\n", tokens->token);
	while (tokens)
	{
		printf("token = %s\n", tokens->token);
		tokens = tokens->next;
	}
}