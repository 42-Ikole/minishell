
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
<<<<<<< HEAD
	while (str[i] >= '\t' || str[i] == ' ')
=======
	while (str[i] == '\t' || str[i] == ' ')
>>>>>>> afcee9e0121c938e6682f9cd9e5287fb954b8e68
		i++;
	if (str[i] == '-')
		nega = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		*err = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	if (str[i])
		*err = -1;
	return (ret * nega);
}

void		do_exit(int code, enum e_bool child)
{
	if (child == false)
		write(1, "exit\n", 5);
	exit(code);
}

int			ft_exit(t_cmd *cmd, enum e_bool child)
{
	int i;
	int	code;
	int err;

	i = 1;
	code = 0;
	err = 0;
	if (!cmd->arg[i])
		do_exit(code, child);
	while (cmd->arg[i])
	{
		code = extoi(cmd->arg[i], &err);
		if (i > 1)
			write(2, "exit: too many arguments\n", 25);
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
