
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
			if (backup_fd[0] < 0 || backup_fd[1] < 0)
				exit (errors("dup failed", 1));
			commands = pipe_stuff(commands);
			if (dup2(backup_fd[0], STDIN_FILENO) == -1)
				exit (errors("dup2 failed", 1));
			if (dup2(backup_fd[1], STDOUT_FILENO) == -1)
				exit (errors("dup2 failed", 1));
			close(backup_fd[0]);
			close(backup_fd[1]);
		}
		else if (commands->type == input)
		{
			commands = redir_input(commands);
		}
		else if (commands->type == trunc || commands->type == append)
		{
			commands = redir_output(commands);
		}
		else
			commands = select_commands(commands, false);
		if (!commands)
			return (1);
		commands = free_cmd(commands);
	}
	return (0);
}
