/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tol <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:56:42 by ivan-tol      #+#    #+#                 */
/*   Updated: 2019/11/20 11:36:12 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static	int		ft_max(unsigned long long index, int i, int nega)
{
	if (index >= 9223372036854775808ULL || i > 19)
	{
		if (nega == 1)
			return (-1);
		else
			return (0);
	}
	return (nega * index);
}

int				ft_atoi(const char *str)
{
	int					i;
	int					nega;
	int					max;
	unsigned long long	index;

	i = 0;
	nega = 1;
	index = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		nega = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		index = index * 10 + str[i] - '0';
		i++;
	}
	max = ft_max(index, i, nega);
	return (max);
}
