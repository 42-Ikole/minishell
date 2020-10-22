
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h>
#include <unistd.h>

int			command_size(t_tokens *tokens)
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

t_cmd		*set_type(t_cmd *commands, char *token)
{
	if (!token)
		commands->type = semicolon;
//	else if (token[0] == '>' && token[1] == '>')
//		commands->type = append;
//	else if (token[0] == '>')
//		commands->type = trunc;
//	else if (token[0] == '<')
//		commands->type = input;
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
		if (ft_ismeta(tokens->token[0]))
		{
			tmp = tokens;
			tokens = tokens->next;
			free (tmp->token);
			free (tmp);
			break ;
		}
		tmp = tokens;
		tokens = tokens->next;
		free (tmp);
	}
	return (tokens);
}

t_cmd		*cmd_splitting(t_tokens **tk)
{
	t_cmd		*commands;
	t_tokens	*tokens;
	int			i;
	int			cmd;

	tokens = *tk;
	commands = malloc(sizeof(t_cmd));
	malloc_check(commands);
	commands->arg = malloc(sizeof(char*) * command_size(tokens) + 1);
	malloc_check(commands->arg);
	commands->type = 0;
	i = 0;
	cmd = command_size(tokens);
	while (tokens)
	{
		if (tokens->token == NULL || ft_ismeta(tokens->token[0]))
		{
			commands = set_type(commands, tokens->token);
			// free(tokens->token); // free node
			// tokens->token = NULL;
			break ;
		}
		commands->arg[i] = tokens->token;
		tokens = tokens->next;
		i++;
	}
	*tk = free_tokens(*tk);
	commands->arg[i] = NULL;
	i = 0;
	while (i < cmd)
	{
		commands->arg[i] = remover(commands->arg[i]);
//		 printf("cmd[%d] = [%s]\n", i, commands->arg[i]);
		i++;
	}
//	 printf("type = %d\n", commands->type);
	return (commands);
}

t_cmd		*parser(t_tokens *tokens)
{
	t_cmd		*commands;
	t_cmd		*head;

	if (!tokens->token)
		return (NULL);
	commands = cmd_splitting(&tokens);
	head = commands;
	commands->read_fd = STDIN_FILENO;
	commands->write_fd = STDOUT_FILENO;
	commands->next = NULL;
	while (tokens)
	{
		commands->next = cmd_splitting(&tokens);
		commands->read_fd = STDIN_FILENO;
		commands->write_fd = STDOUT_FILENO;
		commands = commands->next;
		commands->next = NULL;
	}
	free(tokens);
	if (meta_check(head) < 0)
	{
		while (head)
			head = free_cmd(head);
		return (NULL);
	}
	// for (int i = 0; g_vars->envp[i]; i++) {
	// 	for (int j = 0; g_vars->envp[i][j]; j++)
	// 		printf("%s\n")
	// }
	return (head);
}
