
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
	int				read_fd;
	int				write_fd;
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

void	sig_handler(int signum);

int			prompt(void);

/*
**	ERROR
*/
int			errors(char *msg, int status);
int			malloc_check(void *check);

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
void		sort_env(void);

/*
** Parser
*/
t_cmd		*parser(t_tokens *tokens);
int			command_size(t_tokens *tokens);
// char		*find_replace(char *str, char *find, char *replace);
// char		*ft_replace(char *str, char *find, char *replace, int new_length);
char		*ft_replace_occur(char *str, char *find, char *replace, int idx);
void		parse_env(char **env);
char		*expansion(char *str, int *i);
char		*remover(char *str);
int			meta_check(t_cmd *commands);

/*
** Execute
*/
t_cmd		*select_commands(t_cmd *cmd, enum e_bool child);
int			ft_exit(t_cmd	*cmd, enum e_bool child);
int			change_dir(t_cmd *cmd);
int			ft_get_env(char *str);
int			path_dir(t_cmd	*cmd);
int			print_echo(t_cmd *cmd);
int			builtin_export(t_cmd *cmd);
int			builtin_unset(t_cmd *cmd);
int			builtin_env(t_cmd *cmd);
void		do_exit(int code, enum e_bool child);
t_cmd		*free_cmd(t_cmd *cmd);
int			exec_type(t_cmd *commands);
t_cmd		*pipe_stuff(t_cmd *commands);
t_cmd		*redirect(t_cmd *cmd);
char		*get_path(char	*path, char *exec);

#endif
