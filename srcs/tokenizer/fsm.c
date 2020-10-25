/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/24 10:33:19 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/24 16:03:06 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

int	fsm_space(t_tokens *token, char *line, int start, int i)
{
	while (line[i])
	{
		if (format_de(line, i))
			return (-1);
		format_redirect(line, i);
		if (line[i] == '\\' && ft_iswhitespace(line[i + 1]))
			i += 2;
		if (ft_iswhitespace(line[i]))
		{
			token_addback(token, ft_substr(line, start, i - start));
			return (ft_skip_space(line, i));
		}
		else if (ft_ismeta(line[i]) || line[i] <= append)
		{
			if (start < i)
				token_addback(token, ft_substr(line, start, i - start));
			start = i;
			i = ft_skipmeta(line, i);
			if (i == -1)
			{
				errors("Syntax error", 258);
				return (-1);
			}
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
		if (format_de(line, i))
			return (-1);
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
	return (errors("string expantion!", -1));
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
	return (errors("string expantion!", -1));
}
