/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:11:55 by yisho             #+#    #+#             */
/*   Updated: 2025/05/16 15:14:24 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H

# include "minishell.h"
# include "linked_list.h"

typedef struct s_quote
{
	t_bool	double_quote;
	t_bool	single_quote;
}	t_quote;

typedef struct s_data
{
	pid_t	*child_pids;
	int		child_count;
	int		pipe_fd[2];
	int		last_pid;
	int		exit_code;
	char	*prompt;
	char	**paths;
	t_env	*env;
	t_token	*token;
	t_cmd	*cmd;
	t_quote	quote;
}		t_data;

//print format string in chosen fd
int		printf_fd(int fd, const char *s, ...);
//find environment var
t_env	*find_var(t_env *head, char *name);
//update pwd in the prompt
char	*update_prompt(t_env *env);
void	ft_exit(t_data *data, int exit_code);
void	free_env(t_env **env);

int		check_open_quotes(t_data *data, char *input);
void	handle_quotes(char c, t_quote *quote);

int		dollar_handle(char **input, t_data *data);
int		put_character(char *current_char, char **buffer, t_data *data, int *i);
int		put_dollar(char *input, int *i, char **buffer, t_data *data);
int		check_env_variable(char *input, int *i, t_data *data);
int		handle_special_case(t_data *data, char **buffer, char special_char);
char	*extract_var_name(char *input, int length);
char	*get_env_value(t_env *env, char *name);

t_bool	create_token_list(t_token **head, char *input);

t_bool	check_pipe_syntax(t_data *data);
t_bool	create_cmd_list(t_data *data);
t_bool	setup_command_input(t_data *data, t_token *token, t_cmd *cmd);
t_bool	setup_command_output(t_data *data, t_token *token, t_cmd *cmd);
char	**get_command_arg(t_token *start_token);

//utils
int		ft_is_space(char c);
int		ft_is_special(char *str);
void	print_error(char *msg);
void	print_token_list(t_token *head);
t_bool	is_redirection(t_token_type type);

void	array_clear(char **arr);
t_bool	print_error_token(t_token *token, t_data *data);
void	print_cmd(t_cmd *cmd);

//pipeline
t_bool	execute_pipeline(t_data *data);
void	parent_process(t_data *data, pid_t pid, t_cmd *cmd, t_bool has_next);
void	child_process(t_data *data, t_cmd *cmd, int prev_pipe, t_bool has_next);
void	close_redirections(t_data *data);

t_bool	is_builtin(char *cmd);
t_bool	execute_builtin(t_data *data, t_cmd *cmd);
void	exec_builtin_child(t_cmd *cmd, t_data *data, t_bool has_next);
t_bool	resolve_command_path(t_data *data, t_cmd *cmd, char **path);
char	**env_to_array(t_env *env);
char	*find_cmd_path(t_data *data, char *cmd, t_env *env);
int		here_doc(t_data *data, char *delimiter);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
t_bool	setup_input_redirection(t_cmd *cmd, int prev_pipe);
t_bool	setup_output_redirection(t_cmd *cmd, t_data *data, t_bool has_next);
void	add_child_pid(t_data *data, pid_t pid);
void	init_signals(void);
void	exec_sigint(int sig);

//builtin
int		divide_var(t_env *current, char *env, int exported);
void	add_new_var(t_env *env, char *name, char *value, int to_export);
void	update_env(t_env *env, char *name, char *value);
char	*get_name( char *s);
void	process_cmd(t_data *data, t_cmd *cmd);
char	*get_home(t_data *data);
t_bool	process_input(t_data *data, char *input);
char	*first_word(char *s);
void	process_cd(t_data *data, char **argv);
void	process_pwd(t_data *data);
void	process_env(t_data *data, char **argv);
void	process_export(t_data *data, char **argv);
void	process_unset(t_data *data, char **argv);
void	process_echo(t_data *data, char **argv);
void	process_exit(t_data *data, char **argv);
void	process_other(char *cmd, t_data *data);
void	process_dollar(t_data *data);
void	display_export(t_data *data);
void	update_export(t_env *env, char *name, char *value, int exported);
void	add_empty_export(t_data *data, char *cmd);
void	add_to_env(t_data *data, char *cmd, int i);
int		is_valid(char c);
//other
void	minishell_interactive(t_data *data);
void	update_var(char *var, char *cmd, char *name, char *value);

#endif