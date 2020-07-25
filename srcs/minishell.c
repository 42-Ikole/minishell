
#include "libft.h"
#include "minishell.h"
#include <unistd.h>

int     main(void)
{
	int		ret;
	char	*line;

	while (1)
	{
		write(1, "\e[0;35mFluffeon \e[0;34m➢ \e[0m", 27);
		ret = get_next_line(0, &line);
		if (ret < 0)
			kut_errors("Unable to read line!\n");
		tokenizer(line);
		free(line);
	}
	return (0);
}
