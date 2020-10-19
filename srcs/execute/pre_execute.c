
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int		exec_type(t_cmd *commands)
{
	int		backup_fd[2];

	while (commands)
	{
		if (commands->type == pipeline)
		{
			backup_fd[0] = dup(STDIN_FILENO);
			backup_fd[1] = dup(STDOUT_FILENO);
			commands = pipe_stuff(commands);
			if (dup2(backup_fd[0], STDIN_FILENO) == -1)
				exit (errors("dup2 failed", 1));
			if (dup2(backup_fd[1], STDOUT_FILENO) == -1)
				exit (errors("dup2 failed", 1));
			close(backup_fd[0]);
			close(backup_fd[1]);
			commands = free_cmd(commands);
		}
		else
		{
			commands = select_commands(commands, false);
			if (!commands)
				return (1);
			commands = free_cmd(commands);
		}
	}
	return (0);
}
