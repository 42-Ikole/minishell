/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:07:46 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/26 14:07:50 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void	fork_child(t_cmd *commands, int *fd)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit(errors("dup2 failed", 1));
	close(fd[1]);
	commands = select_commands(commands, true);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (!commands)
		exit(1);
	exit(0);
}

static void	fork_parent(t_cmd *commands, int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(errors("dup2 failed", 1));
	close(fd[0]);
	if (commands->type == pipeline)
		commands = pipe_stuff(commands);
	else
		commands = select_commands(commands, true);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (!commands)
		exit(1);
}

t_cmd		*pipe_stuff(t_cmd *commands)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		exit(errors("pipe could not be initialized", 1));
	pid = fork();
	if (pid < 0)
		do_exit(1, true);
	if (pid > 0)
		fork_parent(commands->next, fd);
	else
		fork_child(commands, fd);
	return (commands);
}
