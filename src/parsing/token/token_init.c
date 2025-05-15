/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:00:00 by yisho             #+#    #+#             */
/*   Updated: 2025/03/26 12:44:18 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

t_token	*token_create(char *str, int type)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return (NULL);
	if (!token_init(new_token, str, type))
	{
		token_clear(&new_token);
		return (NULL);
	}
	return (new_token);
}

t_bool	token_init(t_token *token, char *str, int type)
{
	token->str = NULL;
	token->str = ft_strdup(str);
	//free(str);
	if (!token->str)
		return (FALSE);
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (TRUE);
}
