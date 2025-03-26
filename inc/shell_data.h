/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:11:55 by yisho             #+#    #+#             */
/*   Updated: 2025/03/25 15:42:48 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H

# include "minishell.h"
# include "token.h"

typedef struct s_quote
{
	t_bool	double_quote;
	t_bool	single_quote;
}	t_quote;

typedef struct s_data
{
	int		exit_code;
	t_token	*token;
	t_quote	quote;
	char	**env;
}			t_data;

int		check_open_quotes(t_data *data, char *input);
void	handle_quotes(char c, t_quote *quote);

t_bool	create_token_list(t_token **head, char *input);

//utils
int		ft_is_space(char c);
int		ft_is_special(char *str);
void	print_error(char *msg);

void	print_token_list(t_token *head);

//builtin
void    process_cmd(char *cmd, t_data *data, char ***envp);
char    *first_word(const char *s);
void	process_cd(char *cmd, t_data *data);
void    process_pwd(t_data *data);
void    process_env(t_data *data, char ***envp);
void	process_export(char *cmd, t_data *data, char ***envp);
//void	process_unset(char *cmd, t_data *data);
void    process_echo(char *cmd, t_data *data);
void    process_exit(void);

#endif