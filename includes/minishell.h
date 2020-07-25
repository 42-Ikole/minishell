
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>//

/*
** structs
*/

enum types
{
	none = 0,
	pipeline = 1,
	append = 2,
	trunc = 3,
	input = 4
};

typedef struct s_cmd
{
	char			**arg;
	enum types		type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_nodes
{
	t_cmd			*cmd;
	struct s_nodes	*next;
}	t_nodes;

typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

/*
**	ERROR
*/
void		kut_errors(char *msg);

/*
**	Tokenizer
*/
void		tokenizer(char *line);

#endif
