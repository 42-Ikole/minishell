
#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_cmd	*redir_input(t_cmd *cmd)
{
	int fd;
	int backup;

	backup = dup(STDIN_FILENO);
	if (backup < 0)
		exit (errors("dup failed", 1));
	fd = open(cmd->next->arg[0], O_RDONLY);
	if (fd < 0)
		errors("Error opening file or directory", 1); //
	if (dup2(fd, STDIN_FILENO) == -1)
		exit (errors("dup2 failed", 1));
	close(fd);
	cmd = select_commands(cmd, false);
	close(STDIN_FILENO);
	if (dup2(backup, STDIN_FILENO) == -1)
		exit (errors("dup2 failed", 1));
	close(backup);
	cmd = free_cmd(cmd);
	return (cmd);
}

t_cmd	*redir_output(t_cmd *cmd)
{
	int		fd;
	int 	backup;
	t_cmd	*head;

	backup = dup(STDOUT_FILENO);
	head = cmd;
	while (cmd->type >= append)
	{
		if (backup < 0)
			exit (errors("dup failed", 1));
		if (cmd->type == trunc)
			fd = open(cmd->next->arg[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			fd = open(cmd->next->arg[0], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd < 0)
			errors("Error opening file or directory", 1); //
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit (errors("dup2 failed", 1));
		close(fd);
		cmd = cmd->next;
	}
	head = select_commands(head, false);
	close(STDOUT_FILENO);
	if (dup2(backup, STDOUT_FILENO) == -1)
		exit (errors("dup2 failed", 1));
	close(backup);
	while (head->type >= append)
		head = free_cmd(head);
	return (head);
}
