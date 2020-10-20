
#include "../../includes/minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	backup_io(int	*backup_in, int *backup_out)
{
	*backup_in = dup(STDIN_FILENO);
	*backup_out = dup(STDOUT_FILENO);
	if (*backup_in < 0 || *backup_out < 0)
		exit (errors("dup failed", 1));
}

void	restore_io(int	*backup_fd)
{
	if (dup2(backup_fd[0], STDIN_FILENO) == -1)
		exit (errors("dup2 failed", 1));
	if (dup2(backup_fd[1], STDOUT_FILENO) == -1)
		exit (errors("dup2 failed", 1));
	close(backup_fd[0]);
	close(backup_fd[1]);
}

int		exec_type(t_cmd *commands)
{
	int		backup_fd[2];
	pid_t	pid;

	while (commands)
	{
		if (commands->type == pipeline)
		{
			backup_io(&backup_fd[0], &backup_fd[1]);
			pid = fork();
			if (pid < 0)
				exit (1);
			if (pid == 0)
			{
				commands = pipe_stuff(commands);
				exit (0);
			}
			else
				wait (&pid);
			restore_io(backup_fd);
			while (commands->type == pipeline)
				commands = free_cmd (commands);
		}
		else if (commands->type == trunc || commands->type == append || commands->type == input)
		{
			backup_io(&backup_fd[0], &backup_fd[1]);
			commands = redirect(commands);
			restore_io(backup_fd);
		}
		else
			commands = select_commands(commands, false);
		if (!commands)
			return (1);
		commands = free_cmd(commands);
	}
	return (0);
}
