
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

enum e_bool is_exec(char *exec)
{
	char *path;

	if (!exec)
		return (false);
	if (!(ft_strncmp(exec, "cd", 3)))
		return (true);
	else if (!(ft_cmdcmp(exec, "pwd")))
		return (true);
	else if (!(ft_cmdcmp(exec, "echo")))
		return (true);
	else if (!(ft_strncmp(exec, "exit", 5)))
		return (true);
	else if (!(ft_strncmp(exec, "export", 7)))
		return (true);
	else if (!(ft_strncmp(exec, "unset", 6)))
		return (true);
	else if (!(ft_cmdcmp(exec, "env")))
		return (true);
	else
		path = get_path(g_vars->envp[ft_get_env("PATH")][1], exec);
	if (!path)
		return false;
	free (path);
	return (true);
}

enum e_bool	is_redirect(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[i])
	{
		if (cmd->arg[i][0] <= append)
			return (true);
		i++;
	}
	return (false);
}

int 	redirect(t_cmd *cmd, enum e_bool child)
{
	int		fd;
	int		i;
	int 	j;
	int 	prev;
	t_cmd	exec;
	int 	backup_fd[2];

	i = 0;
	backup_io(&backup_fd[0], &backup_fd[1]);
	while (cmd->arg && cmd->arg[i + 1])
	{
		while (cmd->arg[i][0] > append)
			i++;
		if (cmd->arg[i][0] == input)
			fd = open(cmd->arg[i + 1], O_RDONLY);
		else if (cmd->arg[i][0] == trunc)
			fd = open(cmd->arg[i + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			fd = open(cmd->arg[i + 1], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd < 0)
			errors("Error opening file or directory", 1); //
		if (cmd->arg[i][0] == input)
		{
			close (STDIN_FILENO);
			if (dup2(fd, STDIN_FILENO) == -1)
				exit (errors("dup2 failed", 1));
		}
		else
		{
			close (STDOUT_FILENO);
			if (dup2(fd, STDOUT_FILENO) == -1)
				exit (errors("dup2 failed", 1));
		}
		close(fd);
		i++;
	}
	i = 0;
	prev = 0;
	while (cmd->arg[i])
	{
		if (is_exec(cmd->arg[i]))
		{
			j = prev;
			while (cmd->arg[j][0] > 0)
				j++;
			exec.arg = malloc(sizeof(char*) * j + 1);
			malloc_check(exec.arg);
			j = prev;
			while(cmd->arg[j][0] > 0)
			{
				exec.arg[j] = cmd->arg[j];
				j++;
			}
			exec.arg[j] = NULL;
			exec.type = semicolon;
			exec.next = NULL;
			i++;
			prev = i;
		}
		select_commands(&exec, child);
		free(exec.arg);
		exec.arg = NULL;
		i++;
	}
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	restore_io(backup_fd);
	return (0);
}
