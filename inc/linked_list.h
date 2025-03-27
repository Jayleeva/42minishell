/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:49:27 by yisho             #+#    #+#             */
/*   Updated: 2025/03/27 11:00:10 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "minishell.h"

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

//TOKEN FUNCTION
t_token	*token_create(const char *str, int type);
t_bool	token_init(t_token *token, const	char *str, int type);

t_token	*token_getlast(t_token *head);
t_bool	token_addback(t_token **head, t_token *new_token);
t_bool	token_put_in(t_token **head, const	char *str, int type);

void	token_clear(t_token **token);

//ENV FUNCTION
size_t	env_lenght(t_env *list);

#endif