
#include "libft.h"
#include "minishell.h"
#include <unistd.h>

int     main(void)
{
	int		ret;
	char	*line;
	t_tokens *tokens;
	//something to ignore signals

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
	return (0);
}
