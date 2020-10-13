
//do stuff

#include "stdlib.h"
#include "unistd.h"

void	ft_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
}