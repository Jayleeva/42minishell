/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:11:55 by yisho             #+#    #+#             */
/*   Updated: 2025/04/10 14:32:08 by yisho            ###   ########.fr       */
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
	int		exit_code;
	char	**paths;
	t_env	*env;
	t_token	*token;
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


#endif