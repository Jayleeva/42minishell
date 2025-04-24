/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:20:47 by yishan            #+#    #+#             */
/*   Updated: 2025/03/27 10:50:42 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

size_t	env_lenght(t_env *list)
{
	t_env	*current;
	size_t	i;

	if (list)
	{
		current = list;
		i = 1;
		while (current->next != list)
		{
			i++;
			current = current->next;
		}
		return (i);
	}
	return (0);
}
