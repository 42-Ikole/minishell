
#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <signal.h>

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\b\b  \b\b\n", 7);
		write(1, "\e[0;96mFluffeon \e[0;91m➢\e[0;0m ", 34);
	}
	else
		write(1, "\b\b  \b\b", 6);
}

int		exec_type(t_cmd *commands)
{
	pid_t	pid;
	int		fd[2];

	while (commands)
	{
		if (commands->type == pipeline)
		{
			if (pipe(fd) < 0)
				exit (errors("pipe could not be initialized", 1));
			commands->fd[0] = dup(STDIN_FILENO);
			commands->fd[1] = dup(STDOUT_FILENO);
			if (commands->fd[0] < 0 || commands->fd[1] < 0)
				exit (errors("dup failed!", 1));
			pid = fork();
			if (pid < 0)
				do_exit(1);
			if (pid > 0)
			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO); 
				close(fd[0]); 
				commands = commands->next;
				if (commands->type == pipeline)
					wait(&pid);
				dup2(STDOUT_FILENO, commands->fd[1]);
				dup2(STDIN_FILENO, commands->fd[0]);
				if (STDOUT_FILENO < 0 || STDIN_FILENO < 0)
					exit (errors("dup2 failed", 1));
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

int		prompt(void)
{
	int			ret;
	char		*line;
	t_tokens	*tokens;
	t_cmd		*commands;

	line = NULL;
	while (1)
	{
		if (line)
			free(line);
		write(1, "\e[0;96mFluffeon \e[0;91m➢\e[0;0m ", 34);
		ret = get_next_line(0, &line);
		if (ret < 0)
			return (errors("Unable to read line!\n", 1));
		tokens = tokenizer(line);
		if (!tokens)
			continue ;
		commands = parser(tokens);
		if (!commands)
			continue ;
		exec_type(commands);
		free(line);
		line = NULL;
	}
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	if (ac > 1)
		return (errors("arguments not allowed :(", 1));
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	g_vars->envp = NULL;
	g_vars->ret = 0;
	parse_env(env);
	prompt();
	return (0);
}
