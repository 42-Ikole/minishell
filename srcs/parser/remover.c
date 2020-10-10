
#include "libft.h"
#include "minishell.h"

// later(-1)
// ('), ("), ($)

char *remover(char *str)
{
	int				i;
	int 			even;
	enum e_state	state;
	char 			de[2];

	i = 0;
	even = 0;
	state = space;
	de[0] = (char)-1;
	de[1] = '\0';
	while (str[i])
	{
	    printf("str[i] == [%c]\n", str[i]);
		if (str[i] == '\"' && ((i > 0 && str[i - 1] != '\\') || i == 0) && (!(even % 2) || state == dq))
		{
			state = dq;
			str = ft_replace_occur(str, "\"", "", i);
			even++;
			if (!(even % 2))
				state = space;
		}
		else if (str[i] == '\'' && (!(even % 2) || state == sq))
		{
		    printf("str + i == [%s]\n", str + i);
			state = sq;
			str = ft_replace_occur(str, "\'", "", i);
			even++;
			if (!(even % 2))
				state = space;
		}
		if (str[i] == '$' && ((i > 0 && str[i - 1] != '\\') || i == 0) && state != sq)
			str = expansion(str, &i);
		else
			i++;
	}
	return (str);
}
