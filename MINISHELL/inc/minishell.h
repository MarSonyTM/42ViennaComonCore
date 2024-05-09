/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:16:13 by mafurnic          #+#    #+#             */
/*   Updated: 2024/05/01 13:39:39 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define PROMPT "minishell> "

/* error messages */
# define ERROR "Error"
# define ERR_FIL "no such file or directory"
# define ERR_CMD "command not found"
# define ERR_PERM "permission denied"
# define ERR_INT "interrupted system call"
# define ERR_ARG "invalid argument"
# define ERR_ARGS "too many arguments"
# define ERR_ADDR "bad address"
# define ERR_PARS "syntax error near unexpected token"
# define ERR_NUM "numeric argument required"
# define ERR_VAL "not a valid identifier"

extern sig_atomic_t	g_signal_caught;

/*for expansion before lexer*/

typedef struct s_expansion
{
	int		exit_status;
	char	**cursor;
	char	**result;
}	t_expansion;

/* holds information of each separate token */

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_BUILTIN,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	T_R_OT,
	TOKEN_DOUBLE_REDIRECT_OUT,
	TOKEN_WHITESPACE,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_EXIT_STATUS,
	TOKEN_HEREDOC,
	T_R_OUT_A,
	TOKEN_COMMA,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* holds information of each separate environment variable */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* holds information of each separate command / child process */
typedef struct s_cmd
{
	char			*cmd_path;
	char			**cmd_arr;
	char			**env_vars;
	char			*exit_status_token;
	char			*input;
	char			*output;
	char			*redirection_append;
	int				exit_status;
	int				prev_exit_status;
	int				parse_status;
	struct s_cmd	*next;
}	t_cmd;

/* just reduces variables in execution */
typedef struct s_exec
{
	int	fd[2];
	int	old_fd[2];
	int	processes;
	int	*pid;
	int	*status;
	int	*open_fds;
	int	non_customs;
}	t_exec;

typedef struct s_command
{
	t_token	**current;
	t_cmd	**current_cmd;
	t_cmd	***cmd;
	t_env	**env;
	int		*arg_count;
	int		err_code;
}	t_command;

typedef struct s_lexer
{
	t_env	*env;
	char	*input;
	int		i;
	char	*buffer;
	int		*token_count;
	int		buf_index;
	int		in_quote;
	bool	quote_error;
	bool	lexer_error;
}	t_lexer;

typedef struct s_main_loop
{
	int			exit_status;
	char		*input;
	char		*cursor;
	char		*result;
	t_token		*tokens;
	t_cmd		*cmd;
	t_lexer		lexer_instance;
	t_expansion	exp;
}	t_main_loop;

/*Functions prototypes for Main*/

int				handle_lexer(int lexer_status,
					t_token **tokens, char **input, t_env *env);
int				handle_parser(int parse_status, t_main_loop *loop, t_env *env);
char			*append_to_string(char *str, const char *append);
void			setup_and_handle_input(t_env **env, t_main_loop *loop);
int				execute_and_cleanup(t_env **env, t_main_loop *loop);
int				main_loop(t_env **env);
int				handle_lexer_and_parser(t_env **env, t_main_loop *loop);
void			handle_input_and_expansion(t_env **env, t_main_loop *loop);

/*Functions prototypes for Lexer*/

int				lexer(char *input, t_token **tokens, t_lexer *lexer);
void			free_tokens(t_token **tokens);
int				add_token(t_token **tokens, t_token_type type, char *value);
t_token_type	determine_token_type(char *token, t_lexer *lexer);
t_token_type	handle_first_token(char *token, t_lexer *lexer);
t_token_type	handle_subsequent_tokens(char *token, t_lexer *lexer);
t_token_type	check_special_tokens(char *token);
t_token_type	handle_dollar_tokens(char *token, t_lexer *lexer);
bool			is_command(char *token, t_lexer *lexer);
char			*construct_full_path(char *dir, char *token);
bool			is_whitespace(char c);
void			process_quotes(char currentChar,
					char **buffer, t_lexer *lexer);
int				process_whitespace(char *buffer,
					t_token ***tokens, t_lexer *lexer);
int				process_pipe(char *buffer,
					t_token ***tokens, t_lexer *lexer);
int				process_heredoc(char **buffer,
					t_token ***tokens, t_lexer *lexer );
int				process_single_redirect_out(char *buffer,
					t_token ***tokens, t_lexer *lexer);
int				process_redirect_out_append(char *buffer,
					t_token ***tokens, t_lexer *lexer);
int				process_single_redirect_in(char *buffer,
					t_token ***tokens, t_lexer *lexer);
int				handle_builtin_or_command(t_cmd **cmd,
					t_token *current, t_cmd **current_cmd, int *arg_count);
int				finalize_buffer_and_add_token(char **buffer,
					t_token ***tokens, t_lexer *lexer, char *tokenValue);
int				finalize_lexer(char **buffer,
					t_token ***tokens, t_lexer *lexer, bool quote_error);
void			process_dollar_conditions(char *input, char **buffer,
					t_token ***tokens, t_lexer *lexer);
int				process_input_loop(char *input,
					t_token ***tokens, t_lexer *lexer, bool *quote_error);

/*Functions prototypes for Parser*/

int				parse(t_token *tokens, t_cmd **cmd, t_env *env);
void			free_cmds(t_cmd **cmd);
char			*resolve_command_path(char *command, t_env *env, int *err_code);
t_cmd			*new_command(t_cmd **cmd);
t_cmd			*initialize_new_command(t_cmd **cmd, t_token *current_token,
					t_env *env, int *err_code);
int				add_argument_to_command(t_cmd *current_cmd,
					const char *arg_value);
int				handle_redirection(t_cmd *current_cmd,
					t_token **current, int current_type);
int				handle_exit_status_token(t_cmd *current_cmd,
					char *value, int *arg_count);
t_cmd			*handle_pipe_token(t_command *command);
int				process_tokens(t_token *tokens, t_cmd **cmd, t_env *env);
void			handle_argument(t_cmd *current_cmd,
					t_token *current, int *err_code);
int				handle_input(t_cmd *current_cmd, t_token *current);
int				handle_parser_redirection(t_cmd *current_cmd,
					t_token **current);
int				hdl_parser_heredoc(t_cmd **current_cmd,
					t_token **current, t_command *command);
int				handle_comma(t_cmd *current_cmd, t_token *current);
int				handle_exit_status(t_cmd *current_cmd, t_token *current);
void			link_command_to_list(t_cmd **cmd_list, t_cmd *new_cmd);
t_cmd			*new_command(t_cmd **cmd);
char			*append_line_to_heredoc(char *heredoc_input,
					const char *input_buffer);
char			*handle_heredoc(t_token **current, t_command *command);
void			handle_builtin_or_command_parser(t_command *command);
void			process_token(t_command *command);
char			*ft_strjoin_free_char(char *s1, char c);
char			*ft_strjoin_free(char *s1, const char *s2);
char			*prompt_and_read_line(void);
char			*get_var_name(const char **input);
char			*expand_variable(const char **input,
					char *output, t_command *command);
int				process_command_related_tokens(t_command *command,
					t_token **current, t_cmd **current_cmd);
int				process_other_tokens(t_command *command,
					t_token **current, t_cmd **current_cmd);
char			*expand_variables(const char *input, t_command *command);
int				create_temp_file(char *temp_file_name, int temp_file_num);

/*Functions prototypes for Execution*/

void			custom_exec(t_cmd *cmd,
					t_env **env, t_exec **exec, int stdout_fd);
int				executor(t_cmd *cmd, t_env **env, int exit_status);
t_env			*arr_to_linked_list(char **envp);

/* customs */
void			echo_cmd(t_cmd *cmd);
int				cd_cmd(t_cmd *cmd, t_env *env);
int				pwd_cmd(void);
int				env_cmd(t_cmd *cmd, t_env *env);
void			unset_cmd(t_cmd *cmd, t_env **env);
int				exit_cmd(t_cmd *cmd, t_env *env, t_exec **exec, int stdout_fd);
int				export_cmd(t_cmd *cmd, t_env **env);

/* error management */
void			clean_up(t_cmd *cmd, t_env *env);
void			close_fds(int *open_fds, int processes);
void			close_and_free(t_exec *exec);
void			error(char *msg, char *command, char *argument, int custom);
void			free_array(char **arr);
void			free_env(t_env *env);

/* utils */

int				redirection(t_cmd *cmd, int mode, int custom);
char			**env_to_array(t_cmd *cmd, t_env **env);
int				get_len(t_env *env);
int				count_processes(t_cmd *cmd);
char			*get_key(char *cmd, int *j);
char			*get_value(char *cmd, int *j);
char			*get_value_concat(char *cmd, int *j);
int				handle_custom(t_cmd *cmd, t_env **env, t_exec **exec, int i);
int				handle_pipe(t_exec *exec, int i, char *cmd_path);
int				duplicate_fd(int old_fd, int new_fd, int custom);
char			*ft_getenv(const char *name, t_env *env);
t_env			*add_env_node(t_env **env, char *key, char *value);
int				add_empty_env_var(char *cmd, t_env **env);
int				add_new_env_var(char *cmd, t_env **env, int j);
int				concatenate_env_var(char *cmd, t_env **env, int j);
void			handle_export_args(t_cmd *cmd, t_env **env, int i);
int				get_last_exit_status(t_cmd *cmd, t_exec *exec);
int				allocate_memory(t_exec *exec);
void			handle_fds(t_exec *exec, int i);
void			free_cmds(t_cmd **cmd);
void			reset_free_cmd(t_cmd **cmd, char *input);
void			check_args(int argc, char **argv);
void			init_env_signals(t_env **env, char **envp);
void			update_env_var(t_env *env_var, char *key, char *value);
t_env			*find_env_var(t_env *env, char *key);
int				no_colon(char *cmd, t_env **env, int j);
int				handle_existing_var(t_env *tmp, char *key, char *value);
int				handle_new_var(t_env **env, char *key, char *value);
int				handle_existing_env_var(t_env *tmp, char *key, char *value);
int				handle_new_env_var(t_env **env, char *key, char *value);

/* signal management */
void			handle_sigint(int sig);
void			handle_sigquit(int sig);
void			check_blocked_signals(void);
void			setup_signals(void);
void			heredoc_sigint_handler(int sig);
void			child_setup_signal(void);

/* expansion */
void			process_env_var(char *var_start, t_cmd *cmd, t_env *env);
char			*get_env_value(char *var_name, t_env *env);
void			expand_env_vars(t_env *env, t_expansion *exp,
					char **input, t_main_loop *loop);
int				handle_dollar(t_expansion *exp,
					int in_single_quote, int in_double_quote, t_env *env);
int				handle_space(t_expansion *exp,
					int in_single_quote, int in_double_quote);
void			handle_normal_char(t_expansion *exp);
int				ft_isalnum_expansion(int c);

#endif