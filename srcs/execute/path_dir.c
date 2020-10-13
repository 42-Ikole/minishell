#include "minishell.h"
#include "libft.h"
#include <limits.h>
#include <unistd.h>

void	path_dir(t_cmd *cmd)
{
	(void) cmd;
	char	buf[PATH_MAX + 1];

	if (!getcwd(buf, sizeof(buf)))
	{
		errors("Command pwd not found.");
		return ;
	}
	ft_putendl_fd(buf, 1);
}