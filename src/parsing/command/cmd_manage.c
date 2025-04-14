/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:40:54 by yishan            #+#    #+#             */
/*   Updated: 2025/04/14 14:54:26 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

t_cmd	*cmd_getlast(t_cmd *head)
{
	if (!head)
		return (NULL);
	while (head->next)
	{
		head = head->next;
	}
	return (head);
}

t_bool	cmd_addback(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!head || !new_cmd)
		return (FALSE);
	if (!(*head))
	{
		*head = new_cmd;
		return (TRUE);
	}
	last = cmd_getlast(*head);
	if (!last)
		return (FALSE);
	last->next = new_cmd;
	new_cmd->prev = last;
	new_cmd->next = NULL;
	return (TRUE);
}

t_bool	cmd_put_in(t_cmd**head, int infile, int outfile, char **argv)
{
	t_cmd	*new_cmd;

	new_cmd = cmd_create(infile, outfile, argv);
	if (!new_cmd)
		return (FALSE);
	if (!cmd_addback(head, new_cmd))
	{
		cmd_clear(&new_cmd);
		return (FALSE);
	}
	return (TRUE);
}

size_t	cmd_lenght(t_cmd *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}