
#include <unistd.h>
#include "libft.h"

void	errors(char *msg)
{
	write(2, "\e[0;31mError\e[0m\n\e[0;33m", 25);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
