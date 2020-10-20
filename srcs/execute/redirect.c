
#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_cmd	*redir_output(t_cmd *cmd)
{
	int		fd;
	int 	backup_in;
	int		backup_out;
	t_cmd	*head;

	backup_in = dup(STDIN_FILENO);
	backup_out = dup(STDOUT_FILENO);
	head = cmd;
	if (backup_in < 0 || backup_out < 0)
		exit (errors("dup failed", 1));
	while (cmd->type >= append)
	{
		if (cmd->type == input)
			fd = open(cmd->next->arg[0], O_RDONLY);
		else if (cmd->type == trunc)
			fd = open(cmd->next->arg[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			fd = open(cmd->next->arg[0], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd < 0)
			errors("Error opening file or directory", 1); //
		if (cmd->type == input)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				exit (errors("dup2 failed", 1));
		}
		else
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				exit (errors("dup2 failed", 1));
		}
		close(fd);
		cmd = cmd->next;
	}
	head = select_commands(head, false);
	close(STDIN_FILENO);
	if (dup2(backup_in, STDIN_FILENO) == -1)
		exit (errors("dup2 failed", 1));
	close(STDOUT_FILENO);
	if (dup2(backup_out, STDOUT_FILENO) == -1)
		exit (errors("dup2 failed", 1));
	close(backup_in);
	close(backup_out);
	while (head->type >= append)
		head = free_cmd(head);
	return (head);
}
