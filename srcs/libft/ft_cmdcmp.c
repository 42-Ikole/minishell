
#include "libft.h"

int		ft_cmdcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (!(s1[i] == s2[i] || s1[i] == ft_toupper(s2[i]) || ft_toupper(s1[i]) == s2[i]))
			break ;
		i++;
	}
	if (s1[i] == s2[i] && s1[i] == '\0')
		return (0);
	else
		return (1);
}