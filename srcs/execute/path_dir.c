#include "minishell.h"
#include "libft.h"
#include <limits.h>
#include <unistd.h>

void	path_dir(t_cmd	*cmd)
{
	char	buf[PATH_MAX + 1];

	if (!getcwd(buf, sizeof(buf)))
	{
		errors("pwd failed to get directory", 1);
		return ;
	}
	ft_putendl_fd(buf, cmd->fd[1]);
}
