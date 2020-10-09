
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int		command_size(t_tokens *tokens)
{
	int i;

	i = 0;
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
	else if (token[0] == '>' && token[1] == '>')
		commands->type = input;
	else if (token[0] == '>')
		commands->type = trunc;
	else if (token[0] == '<')
		commands->type = append;
	else if (token[0] == '|')
		commands->type = pipeline;
	else if (token[0] == ';')
		commands->type = semicolon;
	return (commands);
}

t_tokens	*free_tokens(t_tokens *tokens)
{
	t_tokens *tmp;

	while (tokens)
	{
		if (tokens->token == NULL || ft_ismeta(tokens->token[0]))
		{
			tmp = tokens;
			tokens = tokens->next;
			free (tmp);
			return (tokens);
		}
		tmp = tokens;
		tokens = tokens->next;
		free (tmp);
	}
	return (tokens);
}

t_cmd		*cmd_splitting(t_tokens **tk)
{
	t_tokens	*head;
	t_cmd		*commands;
	t_tokens	*tokens;

	tokens = *tk;
	head = tokens;
	int		i;
	commands = malloc(sizeof(t_cmd));
	if (!commands)
		errors("malloc failed!");
	commands->arg = malloc(sizeof(char*) * command_size(tokens) + 1);
	if (!commands->arg)
		errors("malloc failed");
	commands->type = 0;
	i = 0;
	int cmds = command_size(tokens); //alleen voor test purposes
	while (tokens)
	{
		if (tokens->token == NULL || ft_ismeta(tokens->token[0]))
		{
			if (tokens->next && ft_ismeta((tokens->next)->token[0]))
				errors("syntax error.");
			commands = set_type(commands, tokens->token);
			break ;
		}
		commands->arg[i] = tokens->token; 
		tokens = tokens->next;
		i++;
	}
	*tk = free_tokens(tokens);
	commands->arg[i] = NULL;
	for (int j = 0; j < cmds; j++)
		printf("cmd[%d] = [%s]\n", j, commands->arg[j]);
	printf("type = %d\n", commands->type);
	return (commands);
}

t_cmd	*parser(t_tokens *tokens)
{
	t_cmd		*head;
	t_cmd		*commands;

	commands = cmd_splitting(&tokens);
	head = commands;
	commands->next = NULL;
	while (tokens)
	{
		commands->next = cmd_splitting(&tokens);
		commands = commands->next;
		commands->next = NULL;
	}
	free(tokens);
	return (commands);
}
