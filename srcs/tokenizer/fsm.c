
#include "minishell.h"
#include "libft.h"

int	fsm_space(t_tokens *token, char *line, int start, int i)
{
	while (line[i])
	{
		line = format_de(line, i);
		if (line[i] == '\\' && ft_iswhitespace(line[i + 1]))
			i += 2;
		// if (line[i] == '$')
		// 	line = expansion(line, i, '\0');
		if (ft_iswhitespace(line[i]))
		{
			token_addback(token, ft_substr(line, start, i - start));
			return (ft_skip_space(line, i));
		}
		else if (ft_ismeta(line[i]))
		{
			if (start < i)
				token_addback(token, ft_substr(line, start, i - start));
			start = i;
			i = ft_skipmeta(line, i);
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
		line = format_de(line, i);
		// if (line[i] == '$' && ((i > 0 && line[i - 1] != '\\') || i == 0))
		// 	line = expansion(line, i, '\"');
		if (line[i] == '\"' && line[i - 1] != '\\' && (!line[i + 1] ||
			ft_iswhitespace(line[i + 1])) && i != check)
		{
			token_addback(token, ft_substr(line, start, i - start + 1));
			return (ft_skip_space(line, i + 1));
		}
		else if (line[i] == '\'' && i > 0 && line[i - 1] == '\"' &&
			i > check + 1 && line[i - 2] != '\\')
			return (fsm_sq(token, line, start, i));
		else if (line[i] == '\"' && line[i - 1] != '\\' &&
			line[i + 1] && i != check)
			return (fsm_space(token, line, start, i + 1));
		i++;
	}
	return (errors("string expantion!\n", -1));
}

int	fsm_sq(t_tokens *token, char *line, int start, int i)
{
	int check;

	check = i;
	while (line[i])
	{
		if (line[i] == '\'' && (!line[i + 1] ||
			ft_iswhitespace(line[i + 1])) && i != check)
		{
			token_addback(token, ft_substr(line, start, i - start + 1));
			return (ft_skip_space(line, i + 1));
		}
		else if (line[i] == '\"' && i > check + 1 && line[i - 1] == '\'')
			return (fsm_dq(token, line, start, i));
		else if (line[i] == '\'' && line[i + 1] && i != check)
			return (fsm_space(token, line, start, i + 1));
		i++;
	}
	return (errors("string expantion!\n", -1));
}
