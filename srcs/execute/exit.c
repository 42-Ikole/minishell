/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:20:21 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/11/07 10:57:01 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	extoi(const char *str, int *err)
{
	int					i;
	int					nega;
	int					ret;

	i = 0;
	nega = 1;
	ret = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		nega = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		(*err) = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	if (str[i])
		(*err) = -1;
	return (ret * nega);
}

void		do_exit(int code, enum e_bool child)
{
	if (child == false)
		write(2, "exit\n", 5);
	exit(code);
}

int			ft_exit(t_cmd *cmd, enum e_bool child)
{
	int i;
	int	code;
	int err;

	i = 1;
	err = 0;
	if (!cmd->arg[i])
		do_exit(g_vars->ret, child);
	while (cmd->arg[i])
	{
		code = extoi(cmd->arg[i], &err);
		if (i > 1)
			write(2, "exit: too many arguments\n", 25);
		if (i > 1)
			break ;
		else if (err == -1)
		{
			write(2, "exit: numeric argument required\n", 32);
			exit(255);
		}
		else if (!cmd->arg[i + 1])
			do_exit(code, child);
		i++;
	}
	return (-1);
}
