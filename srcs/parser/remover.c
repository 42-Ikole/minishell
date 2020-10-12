
#include "libft.h"
#include "minishell.h"

char *remover(char *str)
{
	int				i;
	int 			even;
	enum e_state	state;

	i = 0;
	even = 0;
	state = space;
	while (str[i])
	{
		if (str[i] == '\"' && ((i > 0 && str[i - 1] != '\\') || i == 0) && (!(even % 2) || state == dq))
		{
			state = dq;
			str = ft_replace_occur(str, "\"", "", i);
			even++;
			if (!(even % 2))
				state = space;
		}
		else if (str[i] == '\'' && ((!(even % 2) && ((i > 0 && str[i - 1] != '\\') || i == 0)) || state == sq))
		{
			state = sq;
			str = ft_replace_occur(str, "\'", "", i);
			even++;
			if (!(even % 2))
				state = space;
		}
		else if (str[i] == '$' && ((i > 0 && str[i - 1] != '\\') || i == 0) && state != sq)
			str = expansion(str, &i);
		else if (str[i - 1] == '\\' && state != sq)
			str = ft_replace_occur(str, "\\", "", i - 1);
		else
			i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)-1)
			str[i] = '\\';
		i++;
	}
	return (str);
}
