
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
	pid_t pid;

	while (commands)
	{
		if (commands->type == pipeline)
		{
			pid = fork();
			if (pid < 0)
				return (errors("fork failed", 1));
			if (pid > 0)
			{
				commands = commands->next;
				if (commands->type != pipeline)
					wait(&pid);
			}
			else
			{
				commands = select_commands(commands);
				commands = free_cmd(commands);
				exit (0);
			}
		}
		else
		{
			commands = select_commands(commands);
			commands = free_cmd(commands);
		}
	}
	return (0);
}

void	prompt(void)
{
	int			ret;
	char		*line;
	t_tokens	*tokens;
	t_cmd		*commands;

	while (1)
	{
		write(1, "\e[0;96mFluffeon \e[0;91m➢\e[0;0m ", 34);
		ret = get_next_line(0, &line);
		if (ret < 0)
		{
			errors("Unable to read line!\n", 1);
			continue ;
		}
		tokens = tokenizer(line);
		commands = parser(tokens);
		exec_type(commands);
		free(line);
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
