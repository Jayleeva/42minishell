/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:11:55 by yisho             #+#    #+#             */
/*   Updated: 2025/03/29 13:53:00 by yishan           ###   ########.fr       */
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
int		handle_special_case(t_data *data, char **buffer, char special_char);
char	*extract_var_name(char *input, int length);
char	*get_env_value(t_env *env, char *name);

t_bool	create_token_list(t_token **head, char *input);

//utils
int		ft_is_space(char c);
int		ft_is_special(char *str);
void	print_error(char *msg);
void	print_token_list(t_token *head);

#endif