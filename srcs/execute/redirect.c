
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

t_cmd	*redirect(t_cmd *cmd)
{
	int		fd;
	t_cmd	*head;

	head = cmd;
	while (cmd->type >= append)
	{
		if (cmd != head && is_exec(cmd->next->arg[0]))
		{
			cmd = cmd->next;
			continue ;
		}
//		printf("cmd->args[0] = %s\n", cmd->arg[0]);
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
	while (head->type >= append)
	{
		if (is_exec(head->arg[0]))
			head = select_commands(head, false);
		head = free_cmd(head);
	}
	return (head);
}
