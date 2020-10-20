/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 15:00:47 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/17 15:28:43 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "../../includes/minishell.h"

static int	ft_nllen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

static void	ft_bufprep(char *buf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	while (buf[i])
	{
		buf[j] = buf[i];
		j++;
		i++;
	}
	buf[j] = '\0';
}

static char	*gnl_strjoin(char *line, char *buf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_nllen(line) + ft_nllen(buf) + 1));
	malloc_check(str);
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	while (buf[j] != '\n' && buf[j] != '\0')
	{
		str[i + j] = buf[j];
		j++;
	}
	str[i + j] = '\0';
	free(line);
	return (str);
}

static int	ft_readline(int fd, char **line, char *buf)
{
	int ret;

	write(1, "  \b\b", 4);
	if (buf[0] == '\0')
	{
		ret = read(fd, buf, 128);
		if (ret == -1)
		{
			free(*line);
			return (-1);
		}
		if (ret == 0 && **line == '\0')
			do_exit(1, false);
		// if (ret == 0)
		// 	return (0);
		buf[ret] = '\0';
	}
	*line = gnl_strjoin(*line, buf);
	if (!*line)
		return (-1);
	if (buf[ft_nllen(buf)] == '\n')
	{
		ft_bufprep(buf);
		return (1);
	}
	buf[0] = '\0';
	return (ft_readline(fd, line, buf));
}

int			get_next_line(int fd, char **line)
{
	static char buf[129];

	if (fd < 0 || read(fd, 0, 0) < 0 || !line)
		return (-1);
	*line = malloc(sizeof(char));
	malloc_check(line);
	**line = '\0';
	return (ft_readline(fd, line, buf));
}
