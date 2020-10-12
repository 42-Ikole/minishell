
#include "minishell.h"

void	meta_check(t_cmd *cmd)
{
	while (cmd)
	{
		if ((cmd->type == semicolon || cmd->type == pipeline) && !cmd->arg[0])
			errors("syntax error 1");
		else if (cmd->type > pipeline && (!cmd->next || !cmd->next->arg[0]))
			errors("syntax error near unexpected token 'newline'");
		else if (cmd->next && cmd->type == cmd->next->type)
			errors("syntax error 3");
		else if (cmd->type == trunc && cmd->next && cmd->next->type == pipeline)
			return ;
		else if (cmd->type == pipeline && cmd->next && cmd->next->type < pipeline)
			errors("syntax error 4");
		// else if (cmd->type != semicolon && (!cmd->next || !cmd->next->arg[0]))
		// 	errors("syntax error 2");
		cmd = cmd->next;
	}	
}
