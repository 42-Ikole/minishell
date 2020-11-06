/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remover.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:06:56 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/01 18:14:09 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"

static int	remove_quote(char **str, int i, enum e_state *state, int *even)
{
	if ((*str)[i] == '\"' && ((i > 0 && (*str)[i - 1] != '\\') ||
	i == 0) && (!(*even % 2) || *state == dq))
	{
		*state = dq;
		(*str) = ft_replace_occur((*str), "\"", "", i);
		(*even)++;
		if (!(*even % 2))
			*state = space;
		return (1);
	}
	else if ((*str)[i] == '\'' && ((!(*even % 2) &&
		((i > 0 && (*str)[i - 1] != '\\') || i == 0)) || *state == sq))
	{
		*state = sq;
		(*str) = ft_replace_occur((*str), "\'", "", i);
		(*even)++;
		if (!(*even % 2))
			*state = space;
		return (1);
	}
	return (0);
}

static char	**expand_stuff(char **str, int *j, int *i, enum e_state *state)
{
	if (str[(*j)][(*i)] == '$' && *state == space && (((*i) > 0 &&
		str[(*j)][(*i) - 1] != '\\') ||
		(*i) == 0) && str[(*j)][(*i) + 1] != '\\')
		str = expansion_space(str, &(*i), j);
	else if (str[(*j)][(*i)] == '$' && *state == dq && (((*i) > 0 &&
		str[(*j)][(*i) - 1] != '\\') || (*i) == 0) &&
		str[(*j)][(*i) + 1] != '\\')
		str[(*j)] = expansion(str[(*j)], &(*i));
	else if ((*i) > 0 && str[(*j)][(*i) - 1] == '\\' && *state == space)
		str[(*j)] = ft_replace_occur(str[(*j)], "\\", "", (*i) - 1);
	else if ((*i) > 0 && str[(*j)][(*i) - 1] == '\\' &&
	!is_escapable(str[*j][*i]) && *state == dq)
		str[(*j)] = ft_replace_occur(str[(*j)], "\\", "", (*i) - 1);
	else if ((*i) > 0 && str[(*j)][(*i) - 1] == '\\' &&
		str[(*j)][(*i)] == '$' && *state == dq)
		str[(*j)] = ft_replace_occur(str[(*j)], "\\", "", (*i) - 1);
	else
		(*i)++;
	return (str);
}

static char	*remove_escaped(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == escaped)
			str[i] = '\\';
		i++;
	}
	return (str);
}

char		**remover(char **str)
{
	int				i;
	int				j;
	int				even;
	enum e_state	state;

	j = 0;
	while (str[j])
	{
		i = 0;
		even = 0;
		state = space;
		while (str[j] && str[j][i])
		{
			if (remove_quote(str + j, i, &state, &even))
				continue ;
			else
				str = expand_stuff(str, &j, &i, &state);
		}
		if (!str[j])
			break ;
		str[j] = remove_escaped(str[j]);
		j++;
	}
	return (str);
}
