/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:58:58 by yisho             #+#    #+#             */
/*   Updated: 2025/03/26 13:36:51 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

t_token	*token_getlast(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
	{
		head = head->next;
	}
	return (head);
}

t_bool	token_addback(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (!head)
		return (FALSE);
	if (!(*head))
	{
		*head = new_token;
		return (TRUE);
	}
	last = token_getlast(*head);
	if (!last)
		return (FALSE);
	last->next = new_token;
	new_token->prev = last;
	return (TRUE);
}

t_bool	token_put_in(t_token **head, const	char *str, int type)
{
	t_token	*new_token;

	new_token = token_create(str, type);
	if (!new_token)
		return (FALSE);
	if (!token_addback(head, new_token))
	{
		token_clear(&new_token);
		return (FALSE);
	}
	if (type == CMD
		&& new_token->prev
		&& (new_token->prev->type == CMD || new_token->prev->type == ARG))
	{
		new_token->type = ARG;
	}
	return (TRUE);
}
