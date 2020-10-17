
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

int		errors(char *msg, int	status)
{
	write(2, "\e[0;31mError\e[0m\n\e[0;33m", 25);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	g_vars->ret = status;
	return (status);
}

int		malloc_check(void *check)
{
	if (check)
		return (0);
	write(2, "\e[0;31mError\e[0m\n\e[0;33m malloc failed!\n", 41);
	g_vars->ret = 1;
	exit (g_vars->ret);
}
