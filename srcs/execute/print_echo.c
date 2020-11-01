/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_echo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:20:02 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/11/01 14:50:54 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	actual_echo(t_cmd *cmd, int i, enum e_bool nl)
{
	while (cmd->arg[i])
	{
		if (cmd->arg[i][0])
			ft_putstr_fd(cmd->arg[i], 1);
		i++;
		if (cmd->arg[i] && cmd->arg[i][0] && !(i == 2 && !cmd->arg[1][0]))
			ft_putchar_fd(' ', 1);
	}
	if (nl == true)
		ft_putchar_fd('\n', 1);
}

int		print_echo(t_cmd *cmd)
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
		if (!cmd->arg[i][j] && j > 1)
			nl = false;
		else if (j == 1)
			break ;
		else
		{
			nl = true;
			break ;
		}
		i++;
	}
	actual_echo(cmd, i, nl);
	return (0);
}
