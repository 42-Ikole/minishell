
#include "minishell.h"
#include "libft.h"

int	fsm_space(t_tokens *token, char *line, int start, int i)
{
	while (line[i])
	{
		if (line[i] == ' ')
		{
			token_addback(token, ft_substr(line, start, i - start));
			return (ft_skip_space(line, i));
		}
		else if (line[i] == '\"' && line[i - 1] != '\\')
			return (fsm_dq(token, line, start, i));
		else if (line[i] == '\'' && line[i - 1] != '\\')
			return (fsm_sq(token, line, start, i));
		i++;
	}
	token_addback(token, ft_substr(line, start, i - start));
	return (i);
}

int	fsm_dq(t_tokens *token, char *line, int start, int i)
{
	int check;

	check = i;
	while (line[i])
	{
		if (line[i] == '\"' && line[i - 1] != '\\' && (!line[i + 1] || line[i + 1] == ' ') && i != check)
		{
			token_addback(token, ft_substr(line, start, i - start + 1));
			return (ft_skip_space(line, i + 1));
		}
		else if (line[i] == '\'' && line[i - 1] != '\\')
			return (fsm_sq(token, line, start, i));
		i++;
	}
	kut_errors("string expantion!\n");
	return (i);
}

int	fsm_sq(t_tokens *token, char *line, int start, int i)
{
	int check;

	check = i;
	while (line[i])
	{
		if (line[i] == '\'' && line[i - 1] != '\\' && (!line[i + 1] || line[i + 1] == ' ') && i != check)
		{
			token_addback(token, ft_substr(line, start, i - start + 1));
			return (ft_skip_space(line, i + 1));
		}
		else if (line[i] == '\"' && line[i - 1] != '\\')
			return (fsm_dq(token, line, start, i));
		i++;
	}
	kut_errors("string expantion!\n");
	return (i);
}
