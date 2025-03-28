/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:11:55 by yisho             #+#    #+#             */
/*   Updated: 2025/03/27 16:20:28 by cyglardo         ###   ########.fr       */
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
	t_env	*env;
	t_token	*token;
	t_quote	quote;
}		t_data;

int		check_open_quotes(t_data *data, char *input);
void	handle_quotes(char c, t_quote *quote);

int		dollar_handle(char **input, t_data *data);
int		put_character(char *current_char, char **buffer, t_data *data, int *i);
int		put_dollar(char *input, int *i, char **buffer, t_data *data);
int		check_env_variable(char *input, int *i, t_data *data);
int		handle_special_case(t_data *data, char **str);

t_bool	create_token_list(t_token **head, char *input);

//utils
int		ft_is_space(char c);
int		ft_is_special(char *str);
void	print_error(char *msg);
void	print_token_list(t_token *head);

//builtin
void    process_cmd(char *cmd, t_data *data);
char    *first_word(char *s);
void	process_cd(char *cmd, t_data *data);
void    process_pwd(t_data *data);
void    process_env(t_data *data);
void	process_export(char *cmd, t_data *data);
void	process_unset(char *cmd, t_data *data);
void    process_echo(char *cmd, t_data *data);
void    process_exit(void);

//other
void    minishell_interactive(int argc, char **argv, t_data *data);
void	update_var(char *var, char *cmd, char *name, char *value);
#endif