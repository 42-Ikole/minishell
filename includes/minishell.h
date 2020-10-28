/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:06:07 by ikole         #+#    #+#                 */
/*   Updated: 2020/10/26 15:42:49 by ivan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdio.h> //

# define PROMPT "\e[0;96mFluffeon \e[0;91m➢\e[0;0m "
# define PROMPT_LENGTH 34

/*
** Globals
*/
typedef struct	s_global
{
	char	***envp;
	int		ret;
}				t_global;

t_global g_vars[1];

/*
** enums
*/

enum			e_state
{
	space,
	sq,
	dq
}				t_state;

enum			e_types {
	semicolon = 0,
	pipeline = 1,
}				t_types;

enum			e_special
{
	escaped = -1,
	append = -2,
	trunc = -3,
	input = -4
}				t_special;

enum			e_bool
{
	true = 1,
	false = 0
}				t_bool;

/*
** structs
*/

typedef struct	s_cmd
{
	char			**arg;
	enum e_types	type;
	int				read_fd;
	int				write_fd;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_nodes
{
	t_cmd			*cmd;
	struct s_nodes	*next;
}				t_nodes;

typedef struct	s_tokens
{
	char			*token;
	struct s_tokens	*next;
}				t_tokens;

/*
**	MAIN
*/
void			sig_handler(int signum);
int				prompt(void);

/*
**	ERROR
*/
int				errors(char *msg, int status);
int				malloc_check(void *check);
void			wait_status(pid_t pid);

/*
**	Tokenizer
*/
t_tokens		*tokenizer(char *line);
t_tokens		*token_addback(t_tokens *tokens, char *token);

/*
** Finite State Machine
*/
int				fsm_space(t_tokens *token, char *line, int start, int i);
int				fsm_dq(t_tokens *token, char *line, int start, int i);
int				fsm_sq(t_tokens *token, char *line, int start, int i);

/*
** Formatter
*/
int				format_de(char *str, int i);
void			sort_env(void);
void			format_redirect(char *str, int i);

/*
** Parser
*/
t_cmd			*parser(t_tokens *tokens);
int				command_size(t_tokens *tokens);
char			*ft_replace_occur
					(char *str, char *find, char *replace, int idx);
void			parse_env(char **env);
char			*expansion(char *str, int *i);
char			**expansion_space(char **str, int *i, int *j);
char			**remover(char **str);
int				meta_check(t_cmd *commands);

/*
** Execute
*/
t_cmd			*select_commands(t_cmd *cmd, enum e_bool child);
int				ft_exit(t_cmd	*cmd, enum e_bool child);
int				change_dir(t_cmd *cmd);
int				ft_get_env(char *str, enum e_bool isnull);
int				path_dir(void);
int				print_echo(t_cmd *cmd);
int				builtin_export(t_cmd *cmd);
int				builtin_unset(t_cmd *cmd);
int				builtin_env(t_cmd *cmd);
void			do_exit(int code, enum e_bool child);
t_cmd			*free_cmd(t_cmd *cmd);
int				exec_type(t_cmd *commands);
enum e_bool		is_exec(char *exec);
t_cmd			*pipe_stuff(t_cmd *commands);
int				redirect(t_cmd *cmd, enum e_bool child);
enum e_bool		is_redirect(t_cmd *cmd, int i);
char			*get_path(char	*path, char *exec);
void			backup_io(int	*backup_in, int *backup_out);
void			restore_io(int	*backup_fd);
int				check_name(char *str);

#endif
