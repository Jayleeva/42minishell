/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:11:55 by yisho             #+#    #+#             */
/*   Updated: 2025/04/14 15:50:43 by cyglardo         ###   ########.fr       */
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
	int		pipe_fd[2];
	pid_t	pid;
	int		exit_code;
	char	**paths;
	t_env	*env;
	t_env	*export;
	t_token	*token;
	//char	**token_list;
	t_cmd	*cmd;
	t_quote	quote;
}		t_data;

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
char	**get_command_arg(t_data *data, t_token *start_token);

//utils
int		ft_is_space(char c);
int		ft_is_special(char *str);
void	print_error(char *msg);
void	print_token_list(t_token *head);
t_bool	is_redirection(t_token_type type);

void	array_clear(char **arr);
t_bool	print_error_token(t_token *token, t_data *data);
void	print_cmd(t_cmd *cmd);

//builtin
char	*get_name(char *cmd);
void    process_token_list(t_data *data, t_token *token_list);
char	*get_home(t_data *data);
t_bool	process_input(t_data *data, char *input);
//void    process_cmd(t_token *token);
//void	process_cmd(char **tab);
void    process_cmd(char *cmd, t_data *data);
char    *first_word(char *s);
void    process_cd(t_data *data, t_token *current);
void    process_pwd(t_data *data);
void    process_env(t_data *data, t_token *current);
void	process_export(t_data *data, t_token *current);
void	process_unset(t_data *data, t_token *current);
void    process_echo(t_data *data, t_token *current);
void    process_exit(t_data *data);
void    process_other(char *cmd, t_data *data);
void    process_dollar(t_data *data);
void	display_export(t_data *data);
void	update_export(t_data *data, char *cmd);
void	update_var_export(char *var, char *cmd);
void	add_empty_export(t_data *data, char *cmd);
void	add_to_env(t_data *data, char *cmd, int i);
//other
void    minishell_interactive(t_data *data);
void	update_var(char *var, char *cmd, char *name, char *value);

#endif