
#include "../../includes/minishell.h"

int	meta_check(t_cmd *cmd) //return value
{
	while (cmd)
	{
		if ((cmd->type == semicolon || cmd->type == pipeline) && !cmd->arg[0])
			return (errors("syntax error 1", 258));
		else if (cmd->type > pipeline && (!cmd->next || !cmd->next->arg[0]))
			return (errors("syntax error near unexpected token 'newline'", 258));
		else if (cmd->next && cmd->type == cmd->next->type &&
			!cmd->next->arg[0])
			return (errors("syntax error 3", 258));
//		else if (cmd->type == trunc && cmd->next &&
//			cmd->next->type == pipeline)
//			return (0);
		else if (cmd->type == pipeline && !cmd->next &&
			cmd->next->type < pipeline)
			return (errors("syntax error 4", 258));
		// else if (cmd->type != semicolon && (!cmd->next || !cmd->next->arg[0]))
		// 	errors("syntax error 2");
		cmd = cmd->next;
	}
	return (0);
}
