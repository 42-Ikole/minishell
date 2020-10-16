
#include "minishell.h"
#include "stdlib.h"

t_cmd	*free_cmd(t_cmd *cmd)
{
	int i;
	t_cmd *next;

	i = 0;
	printf("hier\n");
	while (cmd->arg[i])
	{
		printf("freed [%s]\n", cmd->arg[i]);
		free (cmd->arg[i]);
		i++;
	}
	free(cmd->arg);
	next = cmd->next;
	free (cmd);
	return (next);
}