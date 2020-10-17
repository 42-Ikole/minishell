
#include "minishell.h"

char 	*format_de(char *str, int i)
{
	if (str[i] == '\\' && str[i - 1] == '\\')
			str[i] = (char)-1;
	if (str[i] == '\\' && str[i + 1] == '\0')
		errors("string format faulty", 1); //
	return (str);
}
