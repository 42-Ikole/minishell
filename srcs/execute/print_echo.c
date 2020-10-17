
#include "minishell.h"
#include "libft.h"

int	print_echo(t_cmd *cmd)
{
	int			i;
	enum e_bool	nl;

	i = 1;
	nl = true;
	if (cmd->arg[i] && !ft_strncmp(cmd->arg[i], "-n", 3))
	{
		nl = false;
		i++;
	}
	while(cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], 1);
		i++;
		if (cmd->arg[i])
			ft_putchar_fd(' ', 1);
	}
	if (nl == true)
		ft_putchar_fd('\n', 1);
	return (0);
}
