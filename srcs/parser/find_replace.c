
#include "libft.h"
#include "minishell.h"

char	*ft_replace(char *str, char *find, char *replace, int new_length)
{
	int		i;
	int		j;
	int 	k;
	char	*ret;

	// printf ("new length = %i\n", new_length);
	ret = malloc(sizeof(char) * new_length + 1);
	if (!ret)
		errors("malloc failed!", 1); //
	i = 0;
	j = 0;
	while (i < new_length)
	{
		if (ft_strnstr(str + j, find, ft_strlen(find)))
		{
			k = 0;
			while (replace[k])
			{
				ret[i] = replace[k];
				i++;
				k++;
			}
		    	j += ft_strlen(find);
		}
		else
		{
			ret[i] = str[j];
			i++;
			j++;
		}
	}
	ret[i] = '\0';
	return (ret);
}

char	*find_replace(char *str, char *find, char *replace)
{
	int		i;
	int		count;
	int		new_length;
	char	*ret;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strnstr(str + i, find, ft_strlen(find)))
			count++;
		i++;
	}
	// printf("count = %d\n", count);
	new_length = ft_strlen(str) + (count * (ft_strlen(replace) - ft_strlen(find)));
	ret = ft_replace(str, find, replace, new_length);
	return (ret);
}

char	*ft_replace_occur(char *str, char *find, char *replace, int idx)
{
	int		i;
	int		j;
	int 	k;
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(replace) - ft_strlen(find) + 1));
	if (!ret)
		errors("malloc failed!", 1); //
	i = 0;
	j = 0;
	k = 0;
	while ((unsigned)i < ft_strlen(str) + ft_strlen(replace) - ft_strlen(find))
	{
		if (j == idx)
		{
			while (replace[k])
			{
				ret[i] = replace[k];
				i++;
				k++;
			}
			j += ft_strlen(find);
		}
		else
		{
			ret[i] = str[j];
			i++;
			j++;
		}
	}
	ret[i] = '\0';
	free(str);
	return (ret);
}
