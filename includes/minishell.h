
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>//

/*
** Globals
*/
typedef struct s_global
{
	char	***envp;
	int		ret;
} t_global;

t_global g_vars[1];


/*
** enums
*/

enum e_state
{
	space,
	sq,
	dq
}	t_state;

enum e_types
{
	semicolon = 0,
	pipeline = 1,
	append = 2,
	trunc = 3,
	input = 4
}	t_types;

enum e_bool
{
	true = 1,
	false = 0
}	t_bool;

/*
** structs
*/

typedef struct s_cmd
{
	char			**arg;
	enum e_types	type;
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

void		prompt(void);

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
int			fsm_space(t_tokens *token, char *line, int start, int i);
int			fsm_dq(t_tokens *token, char *line, int start, int i);
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
char		*find_replace(char *str, char *find, char *replace);
char		*ft_replace(char *str, char *find, char *replace, int new_length);
char		*ft_replace_occur(char *str, char *find, char *replace, int idx);
void		parse_env(char **env);
char		*expansion(char *str, int *i);
char		*remover(char *str);
void		meta_check(t_cmd *commands);

/*
** Execute
*/
void		ft_exit(void);

#endif
