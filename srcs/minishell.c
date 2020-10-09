
#include "libft.h"
#include "minishell.h"
#include <unistd.h>

void	prompt(void)
{
	int		ret;
	char	*line;
	t_tokens *tokens;

	while (1)
	{
		write(1, "\e[0;96mFluffeon \e[0;91m➢\e[0;0m ", 34);
		ret = get_next_line(0, &line);
		if (ret < 0)
			errors("Unable to read line!\n");
		tokens = tokenizer(line);
		parser(tokens);
		free(line);
	}
}

int     main(int ac, char **av, char **env)
{
	(void)av;
	if (ac > 1)
		errors("arguments not allowed :(");
	g_vars->envp = NULL;
	g_vars->ret = 0;
	parse_env(env);
	for (int i = 0; g_vars->envp[i]; i++) {
		printf("%s = %s\n", g_vars->envp[i][0], g_vars->envp[i][1]);
	}
	prompt();
	return (0);
}
