/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_dir.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <ivan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:20:12 by ivan-tol      #+#    #+#                 */
/*   Updated: 2020/10/26 14:20:17 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <limits.h>
#include <unistd.h>

int		path_dir(void)
{
	char	buf[PATH_MAX + 1];

	if (!getcwd(buf, sizeof(buf)))
		return (errors("pwd failed to get directory", 1));
	ft_putendl_fd(buf, 1);
	return (0);
}
