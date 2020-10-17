
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
