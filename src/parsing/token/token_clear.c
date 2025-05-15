/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:53:30 by yisho             #+#    #+#             */
/*   Updated: 2025/05/15 12:46:30 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

void	token_clear(t_token **token)
{
	t_token	*current;

	if (token && *token)
	{
		current = *token;
		if (current->str)
		{
			free(current->str);
			current->str = NULL;
		}
		token_clear(&(current->next));
		free (current);
		*token = NULL;
	}
}
