
#include "minishell.h"
#include "libft.h"

int	print_echo(t_cmd *cmd)
{
	int			i;
	int			j;
	enum e_bool	nl;

	i = 1;
	nl = true;
	while (cmd->arg[i] && cmd->arg[i][0] == '-')
	{
		j = 1;
		while (cmd->arg[i][j] == 'n')
			j++;
		if (!cmd->arg[i][j])
			nl = false;
		else
		{
			nl = true;
			break ;
		}
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
