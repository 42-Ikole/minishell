
#include "../../includes/minishell.h"

void 	format_redirect(char *str, int i)
{
	if (str[i - 1] == '\\')
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

void	format_de(char *str, int i)
{
	if (str[i] == '\\' && str[i - 1] == '\\')
			str[i] = escaped;
	if (str[i] == '\\' && str[i + 1] == '\0')
		errors("string format faulty", 1); //
}
