/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pre_execute.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:08:10 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/31 07:18:12 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	sig_skop(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	backup_io(int *backup_in, int *backup_out)
{
	*backup_in = dup(STDIN_FILENO);
	*backup_out = dup(STDOUT_FILENO);
	if (*backup_in < 0 || *backup_out < 0)
		exit(errors("dup failed", 1));
}

void	restore_io(int *backup_fd)
{
	if (dup2(backup_fd[0], STDIN_FILENO) == -1)
		exit(errors("dup2 failed", 1));
	if (dup2(backup_fd[1], STDOUT_FILENO) == -1)
		exit(errors("dup2 failed", 1));
	close(backup_fd[0]);
	close(backup_fd[1]);
}

t_cmd	*pre_pipe_stuff(t_cmd *commands)
{
	int		backup_fd[2];
	pid_t	pid;

	backup_io(&backup_fd[0], &backup_fd[1]);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		pipe_stuff(commands);
		exit(0);
	}
	else
		wait_status(pid);
	restore_io(backup_fd);
	while (commands->type >= pipeline)
		commands = free_cmd(commands);
	return (commands);
}

int		exec_type(t_cmd *commands)
{
	t_cmd	*format;

	signal(SIGINT, sig_skop);
	signal(SIGQUIT, sig_skop);
	while (commands)
	{
		format = commands;
		while (format->type != semicolon)
		{
			format->arg = remover(format->arg);
			format = format->next;
		}
		format->arg = remover(format->arg);
		if (commands->type == pipeline)
			commands = pre_pipe_stuff(commands);
		else
			commands = select_commands(commands, false);
		if (!commands)
			return (1);
		commands = free_cmd(commands);
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (0);
}
