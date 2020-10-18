
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

void	fork_child(t_cmd *commands, int	*fd)
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
	close (fd[0]);
	exit (0);
}

t_cmd	*fork_parent(t_cmd *commands, int	*fd, pid_t	pid)
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
	close (fd[1]);
	return (commands);
}

t_cmd	*pipe_stuff(t_cmd *commands)
{
	pid_t	pid;
	int		fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (pipe(fd) < 0)
		exit (errors("pipe could not be initialized", 1));
	pid = fork();
	if (pid < 0)
		do_exit(1);
	if (pid > 0)
		commands = fork_parent(commands, fd, pid);
	else
		fork_child(commands, fd);
	return (commands);
}
