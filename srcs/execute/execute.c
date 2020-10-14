
#include "libft.h"
#include "minishell.h"

t_cmd	*select_commands(t_cmd *cmd)
{
	if (!cmd->arg[0])
		return (cmd);
	if (!(ft_cmdcmp(cmd->arg[0], "cd")))
		change_dir(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "pwd")))
		path_dir();
	else if (!(ft_cmdcmp(cmd->arg[0], "echo")))
		print_echo(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "exit")))
		builtin_exit(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "export")))
		builtin_export(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "unset")))
		builtin_unset(cmd);
	else if (!(ft_cmdcmp(cmd->arg[0], "env")))
		builtin_env(cmd);
	else
		errors("Command not found");
	return (cmd);
}
