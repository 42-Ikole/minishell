
#include "minishell.h"

void	meta_check(t_cmd *cmd) //return value
{
	while (cmd)
	{
		if ((cmd->type == semicolon || cmd->type == pipeline) && !cmd->arg[0])
		{
			errors("syntax error 1", 1);
			return ;
		}
		else if (cmd->type > pipeline && (!cmd->next || !cmd->next->arg[0]))
		{
			errors("syntax error near unexpected token 'newline'", 1);
			return ;
		}
		else if (cmd->next && cmd->type == cmd->next->type &&
			!cmd->next->arg[0])
		{
			errors("syntax error 3", 1);
			return ;
		}
		else if (cmd->type == trunc && cmd->next &&
			cmd->next->type == pipeline)
			return ;
		else if (cmd->type == pipeline && !cmd->next &&
			cmd->next->type < pipeline)
		{
			errors("syntax error 4", 1);
			return ;
		}
		// else if (cmd->type != semicolon && (!cmd->next || !cmd->next->arg[0]))
		// 	errors("syntax error 2");
		cmd = cmd->next;
	}
}
