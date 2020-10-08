
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>//

/*
** structs
*/

enum state
{
	space,
	sq,
	dq
};

enum types
{
	semicolon = 0,
	pipeline = 1,
	append = 2,
	trunc = 3,
	input = 4
};

enum bool
{
	true = 1,
	false = 0
};

typedef struct s_cmd
{
	char			**arg;
	enum types		type;
	int				input_fd;
	int				output_fd;
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
void		errors(char *msg);

/*
**	Tokenizer
*/
t_tokens	*tokenizer(char *line);
t_tokens	*token_addback(t_tokens *tokens, char *token);

/*
** Finite State Machine
*/
int			fsm_dq(t_tokens *token, char *line, int start, int i);
int			fsm_space(t_tokens *token, char *line, int start, int i);
int			fsm_sq(t_tokens *token, char *line, int start, int i);

/*
** Formatter
*/
char		*format_de(char *str, int i);

/*
** Parser
*/
t_cmd		*parser(t_tokens *tokens);
int			command_size(t_tokens *tokens);

#endif
