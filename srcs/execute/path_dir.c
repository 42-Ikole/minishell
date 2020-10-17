#include "minishell.h"
#include "libft.h"
#include <limits.h>
#include <unistd.h>

int		path_dir(t_cmd	*cmd)
{
	char	buf[PATH_MAX + 1];

	(void)cmd;
	if (!getcwd(buf, sizeof(buf)))
		return (errors("pwd failed to get directory", 1));
	ft_putendl_fd(buf, 1);
	return (0);
}
