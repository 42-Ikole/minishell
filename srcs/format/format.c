/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:07:14 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/31 10:46:52 by ikole         ########   odam.nl         */
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
