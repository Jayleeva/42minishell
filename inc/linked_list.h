/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:49:27 by yisho             #+#    #+#             */
/*   Updated: 2025/05/12 15:43:28 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "minishell.h"

typedef struct s_cmd
{
	t_bool			skip_cmd;
	char			**argv;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*name;
	char			*value;
	int				exported;
	int				added;
	struct s_env	*next;
}	t_env;

//TOKEN FUNCTION
t_token	*token_create(char *str, int type);
t_bool	token_init(t_token *token, char *str, int type);

t_token	*token_getlast(t_token *head);
t_bool	token_addback(t_token **head, t_token *new_token);
t_bool	token_put_in(t_token **head, char *str, int type);

void	token_clear(t_token **token);

//CMD FUNCTION
t_cmd	*cmd_create(int infile, int outfile, char **argv);
t_bool	cmd_init(t_cmd *cmd, int infile, int outfile, char **argv);

t_cmd	*cmd_getlast(t_cmd *head);
t_bool	cmd_addback(t_cmd **head, t_cmd *new_cmd);
t_bool	cmd_put_in(t_cmd**head, int infile, int outfile, char **argv);
size_t	cmd_lenght(t_cmd *list);

void	cmd_clear(t_cmd **cmd);

#endif