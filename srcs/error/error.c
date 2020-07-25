
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	kut_errors(char *msg)
{
	write(2, "\e[0;31mError\e[0m\n\e[0;33m", 39);
	write(2, msg, ft_strlen(msg));
}
