/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:07:14 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/01 13:11:47 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	format_redirect(char *str, int i)
{
	if (i > 0 && str[i - 1] == '\\')
		return ;
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		str[i] = (char)append;
		str[i + 1] = (char)append;
	}
	else if (str[i] == '>')
		str[i] = (char)trunc;
	else if (str[i] == '<')
		str[i] = (char)input;
}

int		format_de(char *str, int i)
{
	if (str[i] == '\\' && str[i - 1] == '\\')
		str[i] = escaped;
	if (str[i] == '\\' && str[i + 1] == '\0')
		return (errors("Multi line commands not supported.", 1));
	return (0);
}

char	*expand_de(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == '\\' && str[i - 1] == '\\')
			str[i] = escaped;
		i++;
	}
	return (str);
}

char	*multiply_escape(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			str = ft_replace_occur(str, "\\", "\\\\", i);
			i++;
		}
		i++;
	}
	return (str);
}
