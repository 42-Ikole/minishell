
#include "libft.h"
#include "minishell.h"

t_cmd	*select_commands(t_cmd *cmd)
{
	if (!(ft_cmdcmp(cmd->arg[0], "cd")))
		change_dir(cmd);
	return (cmd);
}