
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int		exec_type(t_cmd *commands)
{
	pid_t	pid;
	int		fd[2];

	while (commands)
	{
		if (commands->type == pipeline)
		{
			commands->read_fd = dup(STDIN_FILENO);
			commands->write_fd = dup(STDOUT_FILENO);
			fd[0] = STDIN_FILENO;
			fd[1] = STDOUT_FILENO;
			if (pipe(fd) < 0)
				exit (errors("pipe could not be initialized", 1));
			if (fd[0] != STDIN_FILENO)
			{
				if (dup2(commands->read_fd, STDIN_FILENO) == -1)
					exit (errors("dup2 failed 1", 1));
				close (commands->read_fd);
			}
			if (fd[1] != STDOUT_FILENO)
			{
				if (dup2(commands->write_fd, STDOUT_FILENO) == -1)
					exit (errors("dup2 failed 2", 1));
				close (commands->write_fd);
			}
			if (commands->read_fd < 0 || commands->write_fd < 0)
				exit (errors("dup2 failed 3", 1));
			pid = fork();
			if (pid < 0)
				do_exit(1);
			if (pid > 0)
			{
				close(fd[1]);
				if (dup2(fd[0], STDIN_FILENO) == -1)
					exit (errors("dup2 failed 4", 1));
				close(fd[0]); 
				commands = commands->next;
				if (commands->type == pipeline)
					wait(&pid);
				commands = select_commands(commands);
				if (!commands)
					exit (1);
			}
			else
			{
				close (fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				if (fd[1] < 0)
					exit (errors("dup2 failed", 1));
				close(fd[1]); 
				commands = select_commands(commands);
				if (!commands)
					exit (1);
				commands = free_cmd(commands);
				exit (0);
			}
			// if (dup2(commands->read_fd, STDIN_FILENO) == -1)
			// 	exit (errors("dup2 failed 5", 1));
			// if (dup2(commands->write_fd, STDOUT_FILENO) == -1)
			// 	exit (errors("dup2 failed 6", 1));
			// close(commands->read_fd);
			// close(commands->write_fd);
		}
		else
		{
			commands = select_commands(commands);
			if (!commands)
				return (1);
			commands = free_cmd(commands);
		}
	}
	return (0);
}
